//
// Created by tursh on 1/17/19.
//

#pragma once

#include <World/Entities/Entity.h>
#include <Shader/ShaderProgram.h>
#include <map>
#include <World/Entities/Player.h>

namespace CGE
{
    namespace World
    {
        class World
        {
            bool twoD;

            std::map<unsigned int, std::shared_ptr<Entities::Entity>> entities_;

        public:
            World(Entities::Player *player);

            Entities::Player *player;

            Terrain::Terrain *terrain;

            void render();

            void addEntity(std::shared_ptr<Entities::Entity> entity);

            std::shared_ptr<Entities::Entity> getEntity(unsigned int ID);

            const std::map<unsigned int, std::shared_ptr<Entities::Entity>> &getEntities() const;

            void tick();

            void removeEntity(unsigned int ID);

            bool isTwoD() const;

        };
    }
}



