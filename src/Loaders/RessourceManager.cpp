#include "Loader/RessourceManager.h"
#include "Loader/Loader.h"
#include "Loader/Model.h"
#include "Loader/Texture.h"

#include "Utils/Log.h"

#include <map>				
#include <cstdio>			

namespace CGE
{
	namespace Loader
	{

//Index (graphics.index)
// <ID, pair<model ID, texture ID>
		std::map<unsigned int, std::pair<unsigned int, unsigned int>> texModelIndex;
// <ID, path>
		std::map<unsigned int, char *> modelIndex;
// <ID, pair<path, size>
		std::map<unsigned int, std::pair<char *, unsigned int>> texIndex;

		const Data<float> *SQUARE_POSITION;
		const Data<float> *SQUARE_TEX_COORDS;
		const Data<unsigned int> *SQUARE_INDICES;

		//Square data
		const float squareRawPosition[4 * 2] =
		{ -1.0f, -1.0f, //0
		-1.0f, 1.0f, //1
				1.0f, 1.0f, //2
				1.0f, -1.0f //3
				};

		const float squareRawTexCoords[4 * 2] =
		{ 0.0f, 0.0f, //0
		0.0f, 1.0f, //1
				1.0f, 1.0f, //2
				1.0f, 0.0f //3
				};

		const unsigned int squareRawIndices[2 * 3] =
		{ 3, 0, 1, 1, 2, 3 };

		void resManagement::init()
		{
			/*Load index information*/
#define FILEPATH "res/graphics/graphics.index"
			//Open index file
			std::FILE *file;
#if __MINGW32__
			fopen_s(&file, filePath, "r");
#else
			file = fopen(FILEPATH, "r");
#endif
			//Check if the file has been opened correctly
			if (file == nullptr)
				//Print if file could not open
				logError("could not open '" << FILEPATH << "'");

			int line = 0;

			while (true)
			{
				line++;
				//Create buffer for the head of the line
				char head;
				//Get the head of the line
				int res = fscanf(file, "%c", &head, 1);
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
				if (head == 'R')
				{
					//store the ID and the his info
					unsigned int ID;
					std::pair<unsigned int, unsigned int> info;
					fscanf(file, "%u %u %u\n", &ID, &info.first, &info.second);
					texModelIndex[ID] = info;
				}
				//Load Model
				if (head == 'M')
				{
					unsigned int ID;
					char *path = new char[64];
					fscanf(file, "%u %s\n", &ID, path, 64);
					modelIndex[ID] = path;
				}
				//Load Texture
				if (head == 'T')
				{
					unsigned int ID;
					char *path = new char[64];
					unsigned int size;
					fscanf(file, "%u %s %u\n", &ID, path, &size);
					texIndex[ID] = std::make_pair(path, size);
				}
			}

			//Load square model

			SQUARE_POSITION = new Data<float>(squareRawPosition, 4 * 2);
			SQUARE_TEX_COORDS = new Data<float>(squareRawTexCoords, 4 * 2);
			SQUARE_INDICES = new Data<unsigned int>(squareRawIndices, 2 * 3);
		}

//Buffers <ID, Model/Texture>
		std::map<unsigned int, Model *> modelBuf;
		std::map<unsigned int, Texture *> texBuf;

//Check if textured model got already loaded and return it
		TexturedModel resManagement::getTexModel(unsigned int ID)
		{
#ifndef NDEBUG
			if(texModelIndex.find(ID) == texModelIndex.end())
			logError("The textured model: " << ID << " does not exist!");
#endif

			//Get Model and Texture IDs
			std::pair<unsigned int, unsigned int> &pair = texModelIndex[ID];

			//Get Model and Texture and return them in a textured model
			return TexturedModel(getModel(pair.first), getTexture(pair.second));
		}

//Check if model got already loaded and return it
		Model &resManagement::getModel(unsigned int ID)
		{
			//try to get model from buffer
			Model *model = modelBuf[ID];
			if (model == nullptr)
			{
				//If it fail load it from obj file
#ifndef NDEBUG
				//If on debug, check if the model is in index
				if (modelIndex[ID] == nullptr && ID != 0)
					logError("The model with the ID: " << ID << " does not exist.");
#endif //NDEBUG
				//If 0, we want the square model
				if(ID == 0)
					modelBuf[ID] = DataToVAO(*SQUARE_POSITION, *SQUARE_TEX_COORDS, *SQUARE_INDICES, false);
				else
					modelBuf[ID] = loadOBJFile(
						(std::string(R"(res/graphics/models/)") + modelIndex[ID]).data());
				model = modelBuf[ID];
			}
			return *model;
		}

//Check if texture got already loaded and return it
		Texture &resManagement::getTexture(unsigned int ID)
		{
			Texture *tex = texBuf[ID];
			if (tex == nullptr)
			{
#ifndef NDEBUG
				//If on debug, check if the texture is in index
				if (texIndex[ID].first == nullptr)
				{
					logError("The texture with the ID: " << ID << " does not exist.");
				}
#endif
				//If it fail load it from png file
				texBuf[ID] = loadTexture(
						(std::string(R"(res/graphics/textures/)") + texIndex[ID].first).data());
				tex = texBuf[ID];
			}
			return *tex;
		}

		void resManagement::clearBuffers()
		{
			//Destroy and delete models
			for (auto &it : modelBuf)
			{
				it.second->destroy();
				delete it.second;
			}
			modelBuf.clear();

			//Destroy and delete textures
			for (auto &it : texBuf)
			{
				it.second->destroy();
				delete it.second;
			}
			texBuf.clear();
		}

	}
}
