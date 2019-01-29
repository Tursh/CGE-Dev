#include <utility>

#include <unordered_map>
#include <Loader/Loader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Loader/RessourceManager.h>

//
// Created by tursh on 1/25/19.
//

#include "TwoDTerrain.h"

namespace CGE
{
    namespace Terrain
    {

        const float tileSize = 0.05f;

        const glm::mat4 scaledMatrix = glm::scale(glm::mat4(1), glm::vec3(tileSize, tileSize, 0));

        TwoDTerrain::TwoDTerrain(Loader::TexturedModel *background)
                : background_(background)
        {
            //terrainShader->start();
            //terrainShader->loadMatrix(Shader::TRANSFORMATION, glm::scale(glm::mat4(1), glm::vec3(10, 10, 0)));
            //terrainShader->stop();
        }

        TwoDTerrain::~TwoDTerrain()
        {
            delete background_;
            for(auto floor : floors_)
                delete floor.second;
        }

        void TwoDTerrain::render(Shader::BasicShader *terrainShader)
        {

            for (auto tile : tiles_)
            {
                const std::pair<glm::ivec4, unsigned int> &tilesInfo = tile.second;

                for (int x = tilesInfo.first.x; x < tilesInfo.first.y; x++)
                    for (int y = tilesInfo.first.z; y < tilesInfo.first.w; y++)
                    {
                        terrainShader->loadMatrix(Shader::TRANSFORMATION,
                                                  glm::translate(glm::mat4(1),
                                                                 glm::vec3(x, y, 0)));
                        floors_[tilesInfo.second]->render();
                    }
            }
        }

        void TwoDTerrain::renderBackground()
        {
            background_->render();
        }

        /*
        static std::shared_ptr<Loader::Model> createRoomModel(glm::ivec4 data)
        {
            int width = data.y - data.x, height = data.w - data.z;
            auto tileCount = static_cast<unsigned int>(width * height);
            auto *positions = new float[2 * 4 * tileCount];   //vec2
            auto *texCoords = new float[2 * 4 * tileCount];   //vec2
            auto *indices = new unsigned int[2 * 3 * tileCount];  //index

            unsigned int tileIndex = 0;

            for (int x = 0; x < width; x++)
                for (int y = 0; y < height; y++)
                {
                    unsigned int index = 2 * 4 * tileIndex;
                    //top left
                    positions[index] = data.x + x;
                    positions[index + 1] = data.z + y;
                    texCoords[index] = 0;
                    texCoords[index + 1] = 1;
                    //top right
                    positions[index + 2] = data.x + x + 1;
                    positions[index + 3] = data.z + y;
                    texCoords[index + 2] = 1;
                    texCoords[index + 3] = 1;
                    //bottom right
                    positions[index + 4] = data.x + x + 1;
                    positions[index + 5] = data.z + y + 1;
                    texCoords[index + 4] = 1;
                    texCoords[index + 5] = 0;
                    //bottom left
                    positions[index + 6] = data.x + x;
                    positions[index + 7] = data.x + y + 1;
                    texCoords[index + 6] = 0;
                    texCoords[index + 7] = 0;

                    unsigned int vertexIndex = 2 * 3 * index;
                    indices[vertexIndex] = tileIndex * 4;
                    indices[vertexIndex] = tileIndex * 4 + 1;
                    indices[vertexIndex] = tileIndex * 4 + 2;
                    indices[vertexIndex] = tileIndex * 4 + 2;
                    indices[vertexIndex] = tileIndex * 4 + 3;
                    indices[vertexIndex] = tileIndex * 4;

                    tileIndex++;
                }

            Loader::Data positionsData(positions, 2 * 4 * tileCount);
            Loader::Data texCoordsData(texCoords, 2 * 4 * tileCount);
            Loader::Data indicesData(indices, 2 * 3 * tileCount);

            auto model =  Loader::DataToVAO(positionsData, texCoordsData, indicesData, false);

            //Delete arrays
            delete[] positions, texCoords, indices;

            return model;
        }
         */

        unsigned int TwoDTerrain::addTiles(std::pair<glm::ivec4, unsigned int> tiles)
        {
            if(floors_.find(tiles.second) == floors_.end())
                floors_[tiles.second] = Loader::resManagement::getTexModel(tiles.second);
            tiles_[futurID_] = tiles;
            return futurID_++;
        }

        void TwoDTerrain::tick(Entities::Player *player)
        {
            //TODO: Check what tiles to draw
            //terrainShader->start();
            //terrainShader->loadMatrix(Shader::VIEW, player->getCamera()->toViewMatrix(player));
            //terrainShader->stop();
        }

    }
}