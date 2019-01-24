//
// Created by tursh on 1/17/19.
//

#include <World/World.h>
#include <Renderer/WorldRenderer.h>
#include <Utils/Log.h>

namespace CGE
{
    namespace World
    {

        void World::render()
        {
            Renderer::WorldRenderer::render(*this);
        }

        void World::addEntity(Entities::Entity *entity)
        {
            entities_[entity->ID] = entity;
        }

        const std::map<unsigned int, Entities::Entity *> &World::getEntities() const
        {
            return entities_;
        }

        void World::removeEntity(unsigned int ID)
        {
#ifndef NDEBUG
            if (entities_.find(ID) == entities_.end())
            logError("The entity(ID: " << ID << ") does not exist.");
#endif
            entities_.erase(ID);
        }

        World::World(Entities::Player *player)
                : player(player)
        {

        }

        Entities::Entity *World::getEntity(unsigned int ID)
        {
#ifndef NDEBUG
            if (entities_.find(ID) == entities_.end())
            logError("The entity(ID: " << ID << ") does not exist.");
#endif
            return entities_[ID];
        }
    }
}