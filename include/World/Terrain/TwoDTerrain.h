//
// Created by tursh on 1/25/19.
//

#pragma once

#include <memory.h>
#include "Terrain.h"
#include <Loader/Texture.h>
#include <vector>
#include <Loader/Models/TexturedModel.h>
#include <map>
#include <Shader/ModelShader/BasicShader.h>
#include <View/Camera.h>

namespace CGE
{
    namespace Terrain
    {

        class TwoDTerrain : public Terrain
        {
            bool animatedBackground;
            Loader::TexturedModel *background_;
            std::map<unsigned int, Loader::TexturedModel *> floors_;
            //<ID, <coords(x = xstart, y = ystart, z = xend, w = yend, floorID>>
            std::map<unsigned int, std::pair<glm::ivec4, unsigned int>> tiles_;
            //<ID, roomModel>
            //std::map<unsigned int, std::shared_ptr<Loader::Model>> roomModels_;

            unsigned int futurID_ = 0;
        public:
            TwoDTerrain(Loader::TexturedModel *background);

            ~TwoDTerrain();

            void tick(Entities::Player *player);

            void render(Shader::BasicShader *terrainShader);

            void renderBackground();

            //return ID;
            unsigned int addTiles(std::pair<glm::ivec4, unsigned int> tiles);
        };

    }
}
