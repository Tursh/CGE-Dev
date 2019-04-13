#include "Loader/RessourceManager.h"

#include <map>
#include <Loader/RessourceManager.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <Utils/GLDebug.h>


namespace CGE::Loader
    {

        //Index (graphics.index)
        // <ID, pair<model ID, texture ID>
        std::map<unsigned int, std::pair<unsigned int, unsigned int>> texModelIndex;
        // <ID, path>
        std::map<unsigned int, char *> modelIndex;
        // <ID, path>
        std::map<unsigned int, char *> texIndex;
        // <ID, pair<std::vector<texID>, size>
        std::map<unsigned int, std::pair<std::vector<unsigned int>, float>> twoDAniIndex;
        // <ID, .anim path>
        std::map<unsigned int, char *> animationIndex;

        const Data<float> *SQUARE_POSITION;
        const Data<float> *SQUARE_TEX_COORDS;
        const Data<unsigned int> *SQUARE_INDICES;

        //Square data
        const float squareRawPosition[4 * 2] =
                {-1.0f, -1.0f, //0
                 -1.0f, 1.0f, //1
                 1.0f, 1.0f, //2
                 1.0f, -1.0f //3
                };

        const float squareRawTexCoords[4 * 2] =
                {0.0f, 0.0f, //0
                 0.0f, 1.0f, //1
                 1.0f, 1.0f, //2
                 1.0f, 0.0f //3
                };

        const unsigned int squareRawIndices[2 * 3] =
                {3, 0, 1, 1, 2, 3};

        void resManager::init()
        {
            /*Load index information*/
#define FILEPATH "res/graphics/graphics.index"
            //Open index file
            std::FILE *file;
#if 0
            fopen_s(&file, filePath, "r");
#else
            file = fopen(FILEPATH, "r");
#endif
            //Check if the file has been opened correctly
            if (file == nullptr)
                //Print if file could not open
            logError("could not open '" << FILEPATH << "'");

            unsigned int lineCount = 0;
            while (true)
            {
                lineCount++;
                //Create buffer for the head of the line
                char head;
                //Get the head of the line
                int res = fscanf(file, "%c", &head);
                //Check if it's the end of file (EOF)
                if (res == EOF)
                    break;
                //Comments
                if (head == '#')
                {
                    //Skip the line
                    char line[100];
                    fgets(line, 100, file);
                }
                    //Load TexModel
                else if (head == 'R')
                {
                    //store the ID and the his info
                    unsigned int ID;
                    std::pair<unsigned int, unsigned int> info;
                    fscanf(file, "%u %u %u\n", &ID, &info.first, &info.second);
                    texModelIndex[ID] = info;
                }
                    //Load Model
                else if (head == 'M')
                {
                    unsigned int ID;
                    char *path = new char[64];
                    fscanf(file, "%u %s\n", &ID, path, 64);
                    modelIndex[ID] = path;
                }
                    //Load Texture
                else if (head == 'T')
                {
                    unsigned int ID;
                    char *path = new char[64];
                    fscanf(file, "%u %s\n", &ID, path);
                    texIndex[ID] = path;
                }
                    //Load 2D animation
                else if (head == 'D')
                {
                    unsigned int ID, size;
                    fscanf(file, "%u %u ", &ID, &size);
                    std::vector<unsigned int> texIDs;
                    texIDs.reserve(size);
                    for (unsigned int i = 0; i < size; i++)
                    {
                        unsigned int texID;
                        fscanf(file, "%u ", &texID);
                        texIDs.push_back(texID);
                    }
                    float scale;
                    fscanf(file, "%f\n", &scale);
                    twoDAniIndex[ID] = std::make_pair(texIDs, scale);
                }
                    //Load Animation info
                else if (head == 'A')
                {
                    unsigned int ID;
                    char *path = new char[64];
                    fscanf(file, "%u %s\n", &ID, path);
                    animationIndex[ID] = path;
                }
                    //Unknown Head
                else
                {
                    logWarning("There is an unknown head at line " << lineCount << " in " << FILEPATH);
                    //Skip the line
                    char line[100];
                    fgets(line, 100, file);
                }
            }

            //Check of the 2D animation has all the textures
#ifndef NDEBUG
            for (const auto animation : twoDAniIndex)
                for (const auto texture : animation.second.first)
                    if (texIndex.find(texture) == texIndex.end())
                    logError("Texture with ID: " << texture << "does not exist.");
#endif

            //Load square model

            SQUARE_POSITION = new Data<float>(squareRawPosition, 4 * 2);
            SQUARE_TEX_COORDS = new Data<float>(squareRawTexCoords, 4 * 2);
            SQUARE_INDICES = new Data<unsigned int>(squareRawIndices, 2 * 3);
        }

        //Buffers <ID, Model/Texture>
        std::map<unsigned int, std::weak_ptr<TexturedModel>> texModelBuf;
        std::map<unsigned int, std::weak_ptr<Model>> modelBuf;
        std::map<unsigned int, std::weak_ptr<Texture[]>> texBuf;
        std::map<unsigned int, std::weak_ptr<TwoDAnimatedModel>> twoDAniModelBuf;
        std::map<unsigned int, std::weak_ptr<Texture[]>> twoDAniBuf;

        //Check if textured model got already loaded and return it
        std::shared_ptr<TexturedModel> resManager::getTexModel(unsigned int ID)
        {
#ifndef NDEBUG
            if (texModelIndex.find(ID) == texModelIndex.end())
            logError("The textured model: " << ID << " does not exist!");
#endif
            std::shared_ptr<TexturedModel> texModel;
            start:
            if (texModelBuf.find(ID) == texModelBuf.end())
            {
                //Get Model and Texture IDs
                std::pair<unsigned int, unsigned int> &pair = texModelIndex[ID];
                texModel = std::make_shared<TexturedModel>(getModel(pair.first), getTexture(pair.second),
                                                           (pair.first) ? Basic3DTexturedModel : Basic2DTexturedModel);
                texModelBuf[ID] = texModel;
            } else
            {
                std::weak_ptr buf = texModelBuf[ID];
                if(buf.expired())
                {
                    texModelBuf.erase(ID);
                    goto start;
                }
                texModel = buf.lock();
            }
            return texModel;
        }

        //Check if model got already loaded and return it
        std::shared_ptr<Model> resManager::getModel(unsigned int ID)
        {
            std::shared_ptr<Model> model;
            start:
            //check if the model is loaded
            if (modelBuf.find(ID) == modelBuf.end())
            {
                //If it fail load it from obj file
#ifndef NDEBUG
                //If on debug, check if the model is in index
                if (modelIndex[ID] == nullptr && ID != 0)
                logError("The model with the ID: " << ID << " does not exist.");
#endif //NDEBUG
                //If 0, we want the square model
                //logInfo("Model with ID: " << ID << "got loaded. ");
                if (ID == 0)
                    model = DataToVAO(*SQUARE_POSITION, *SQUARE_TEX_COORDS, *SQUARE_INDICES, false);
                else
                    model = loadOBJFile((std::string(R"(res/graphics/models/)") + modelIndex[ID]).data());
                modelBuf[ID] = model;
            } else
            {
                if (modelBuf[ID].expired())
                {
                    modelBuf.erase(ID);
                    goto start;
                }
                model = modelBuf[ID].lock();
            }

            return model;
        }

        //Check if texture got already loaded and return it
        std::shared_ptr<Texture[]> resManager::getTexture(unsigned int ID)
        {
            std::shared_ptr<Texture[]> tex;
            start:
            if (texBuf.find(ID) == texBuf.end())
            {
#ifndef NDEBUG
                //If on debug, check if the texture is in index
                if (texIndex[ID] == nullptr)
                {
                    logError("The texture with the ID: " << ID << " does not exist.");
                }
#endif
                //If it fail load it from png file
                tex = std::shared_ptr<Texture[]>(new Texture[1]);
                tex[0].loadTexture(texIndex[ID]);
                texBuf[ID] = tex;
            } else
            {
                if (texBuf[ID].expired())
                {
                    texBuf.erase(ID);
                    goto start;
                }
                tex = texBuf[ID].lock();
            }

            return tex;
        }

        std::shared_ptr<TwoDAnimatedModel> resManager::getFlat2DAnimation(unsigned int ID)
        {
            std::shared_ptr<TwoDAnimatedModel> twoDAniModel;
            start:
            if (twoDAniModelBuf.find(ID) == twoDAniModelBuf.end())
            {
                //Get Model and Texture IDs
                std::pair<std::vector<unsigned int>, float> &pair = twoDAniIndex[ID];
                twoDAniModel = std::make_shared<TwoDAnimatedModel>(getModel(0),
                                                                get2DAnimationTextures(ID),
                                                                (unsigned int) pair.first.size(),
                                                                pair.second,
                                                                new Animations::TextureAnimation(animationIndex[ID]));
                twoDAniModelBuf[ID] = twoDAniModel;
            } else
            {
                std::weak_ptr buf = twoDAniModelBuf[ID];
                if(buf.expired())
                {
                    twoDAniModelBuf.erase(ID);
                    goto start;
                }
                twoDAniModel = buf.lock();
            }
            return twoDAniModel;
        }

        std::shared_ptr<Texture[]> resManager::get2DAnimationTextures(unsigned int ID)
        {
            std::shared_ptr<Texture[]> textures;
            start:
            if (twoDAniBuf.find(ID) == twoDAniBuf.end())
            {
                std::vector<unsigned int> textureIDs = twoDAniIndex[ID].first;
                auto count = (unsigned int) textureIDs.size();
#ifndef NDEBUG
                if (count == 0)
                logError("The 2D animation with the ID: " << ID << " does not exist.");
#endif
                //Get the texture path to load
                std::vector<const char *> texturePaths;
                texturePaths.reserve(count);
                for (auto texID : textureIDs)
                    texturePaths.push_back(texIndex[texID]);

                textures = std::shared_ptr<Texture[]>(loadTextures(&texturePaths[0], count));

                twoDAniBuf[ID] = textures;
            } else
            {
                std::weak_ptr buf = twoDAniBuf[ID];
                if(buf.expired())
                {
                    twoDAniBuf.erase(ID);
                    goto start;
                }
                textures = twoDAniBuf[ID].lock();
            }
            return textures;
        }

        std::vector<unsigned int> textureToClear;
        std::vector<std::tuple<unsigned int, std::vector<unsigned int>>> modelToClear;

        void resManager::clear()
        {
            for (auto &texture : textureToClear)
            {
                logInfo("delete texture ID: " << texture);
                if (texture != 0xffffffff)
                    GLCall(glDeleteTextures(1, &texture));
            }
            textureToClear.clear();
            for(const auto &model : modelToClear)
            {
                auto &VAO = std::get<0>(model);
                auto &VBOs = std::get<1>(model);
                //Delete VAO
                GLCall(glDeleteVertexArrays(1, &VAO));

                //Delete VBOs
                for (unsigned int VBO : VBOs)
                {
                    GLCall(glDeleteBuffers(1, &VBO));
                }
            }
            modelToClear.clear();
        }

        void trashTexture(unsigned int texture)
        {
            textureToClear.push_back(texture);
        }

        void trashModel(std::tuple<unsigned int, std::vector<unsigned int>> model)
        {
            modelToClear.push_back(model);
        }

    }
