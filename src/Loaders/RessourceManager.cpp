#include <memory>

#include "Loader/RessourceManager.h"

#include <Utils/Log.h>
#include <map>
#include <GL/glew.h>
#include <Utils/GLDebug.h>


namespace CGE::Loader
{

    //Index (graphics.index)
    // <ID, pair<model ID, texture ID>
    static std::map<unsigned int, std::pair<unsigned int, unsigned int>> texMeshIndex;
    // <ID, path>
    static std::map<unsigned int, char *> modelIndex;
    // <ID, <path, atlas size>>
    static std::map<unsigned int, std::tuple<char *, glm::ivec2>> texIndex;
    // <ID, .anim path>
    static std::map<unsigned int, char *> animationIndex;

    static const Data<float> *SQUARE_POSITION;
    static const Data<float> *SQUARE_TEX_COORDS;
    static const Data<unsigned int> *SQUARE_INDICES;

    //Square data
    static const float squareRawPosition[4 * 2] =
            {-1.0f, -1.0f, //0
             -1.0f, 1.0f, //1
             1.0f, 1.0f, //2
             1.0f, -1.0f //3
            };

    static const float squareRawTexCoords[4 * 2] =
            {0.0f, 0.0f, //0
             0.0f, 1.0f, //1
             1.0f, 1.0f, //2
             1.0f, 0.0f //3
            };

    static const unsigned int squareRawIndices[2 * 3] =
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
        {
            //Print if file could not open
            logWarning("could not open '" << FILEPATH << "'" << ".");
            logWarning("The resource manager did not initialize correctly!");
            return;
        }

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
                //Load TexMesh
            else if (head == 'R')
            {
                //store the ID and the his info
                unsigned int ID;
                std::pair<unsigned int, unsigned int> info;
                fscanf(file, "%u %u %u\n", &ID, &info.first, &info.second);
                texMeshIndex[ID] = info;
            }
                //Load Mesh
            else if (head == 'M')
            {
                unsigned int ID;
                char *path = new char[64];
                fscanf(file, "%u %s\n", &ID, path);
                modelIndex[ID] = path;
            }
                //Load Texture
            else if (head == 'T')
            {
                unsigned int ID;
                char *path = new char[64];
                glm::ivec2 size;
                fscanf(file, "%u %s %u %u\n", &ID, path, &size.x, &size.y);
                texIndex[ID] = std::make_tuple(path, size);
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

        //Load square model

        SQUARE_POSITION = new Data<float>(squareRawPosition, 4 * 2);
        SQUARE_TEX_COORDS = new Data<float>(squareRawTexCoords, 4 * 2, GL_DYNAMIC_DRAW);
        SQUARE_INDICES = new Data<unsigned int>(squareRawIndices, 2 * 3);
    }

    void resManager::terminate()
    {
        for (auto index : modelIndex)
            delete[] index.second;
        for (auto index : texIndex)
            delete[] std::get<0>(index.second);
        for (auto index : animationIndex)
            delete[] index.second;
    }

    //Buffers <ID, Mesh/Texture>
    std::map<unsigned int, std::weak_ptr<TexturedMesh>> texMeshBuf;
    std::map<unsigned int, std::weak_ptr<Mesh>> modelBuf;
    std::map<unsigned int, std::weak_ptr<Texture>> texBuf;
    std::map<unsigned int, std::weak_ptr<TwoDAnimatedMesh>> twoDAniMeshBuf;
    std::map<unsigned int, std::weak_ptr<Texture>> twoDAniBuf;

    //Check if textured model got already loaded and return it
    SharedTexMesh resManager::getTexMesh(unsigned int ID)
    {
#ifndef NDEBUG
        if (texMeshIndex.find(ID) == texMeshIndex.end())
        logError("The textured model: " << ID << " does not exist!")
#endif
        SharedTexMesh texMesh;
        start:
        if (texMeshBuf.find(ID) == texMeshBuf.end())
        {
            //Get Mesh and Texture IDs
            std::pair<unsigned int, unsigned int> &pair = texMeshIndex[ID];
            texMesh = std::make_shared<TexturedMesh>(getMesh(pair.first), getTexture(pair.second), pair.first);
            texMeshBuf[ID] = texMesh;
        } else
        {
            std::weak_ptr buf = texMeshBuf[ID];
            if (buf.expired())
            {
                texMeshBuf.erase(ID);
                goto start;
            }
            texMesh = buf.lock();
        }
        return texMesh;
    }

    //Check if model got already loaded and return it
    SharedMesh resManager::getMesh(unsigned int ID)
    {
        SharedMesh model;
        start:
        //check if the model is loaded
        if (modelBuf.find(ID) == modelBuf.end())
        {
            //If it fail load it from obj file
#ifndef NDEBUG
            //If on debug, check if the model is in index
            if (modelIndex[ID] == nullptr && ID != 0)
            logError("The model with the ID: " << ID << " does not exist.")
#endif //NDEBUG
            //If 0, we want the square model
            //logInfo("Mesh with ID: " << ID << "got loaded. ");
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
    SharedTexture resManager::getTexture(unsigned int ID)
    {
        SharedTexture tex;
        start:
        if (texBuf.find(ID) == texBuf.end())
        {
            auto texInfo = texIndex[ID];
#ifndef NDEBUG
            //If on debug, check if the texture is in index
            if (std::get<0>(texInfo) == nullptr)
            {
                logError("The texture with the ID: " << ID << " does not exist.")
            }
#endif
            //If it fail load it from png file
            tex = std::make_shared<Texture>(std::get<1>(texInfo));
            tex->loadTexture(std::get<0>(texInfo));
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

    std::vector<unsigned int> textureToClear;
    std::vector<std::tuple<unsigned int, std::vector<unsigned int>>> modelToClear,
            modelToClearExtraBuffer; //* < For multithreading memory management

    void resManager::scrap()
    {
        for (auto &texture : textureToClear)
        {
#ifndef NDEBUG
            logInfo("delete texture ID: " << texture);
#endif
            if (texture != 0xffffffff)
            GLCall(glDeleteTextures(1, &texture))
        }
        textureToClear.clear();
        modelToClear.swap(modelToClearExtraBuffer);
        for (const auto &model : modelToClear)
        {
            auto &VAO = std::get<0>(model);
            auto &VBOs = std::get<1>(model);
            //Delete VAO
            GLCall(glDeleteVertexArrays(1, &VAO))

            //Delete VBOs
            for (unsigned int VBO : VBOs)
            {
                GLCall(glDeleteBuffers(1, &VBO))
            }
        }
        modelToClear.clear();

    }

    void trashTexture(unsigned int texture)
    {
        textureToClear.push_back(texture);
    }

    void trashMesh(const std::tuple<unsigned int, std::vector<unsigned int>> &model)
    {
        modelToClearExtraBuffer.push_back(model);
    }

}

template
struct CGE::Loader::Data<float>;
template
struct CGE::Loader::Data<unsigned int>;