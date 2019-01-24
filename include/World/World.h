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

            std::map<unsigned int, Entities::Entity *> entities_;

        public:
            World(Entities::Player *player);

            Entities::Player *player;

            void render();

            void addEntity(Entities::Entity *entity);

            Entities::Entity *getEntity(unsigned int ID);

            const std::map<unsigned int, Entities::Entity *> &getEntities() const;

            void removeEntity(unsigned int ID);

        };
    }
}



