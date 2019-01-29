//
// Created by tursh on 1/17/19.
//

#include <World/World.h>
#include <Renderer/WorldRenderer.h>
#include <Utils/Log.h>
#include <World/Terrain/TwoDTerrain.h>
#include <Loader/RessourceManager.h>

namespace CGE
{
    namespace World
    {

        World::World(Entities::Player *player)
                : player(player),
                  terrain(new Terrain::TwoDTerrain(Loader::resManagement::getTexModel(5))),
                  twoD(player->isTwoD())
        {
            entities_[player->ID] = std::shared_ptr<Entities::Entity>(player);
        }


        void World::render()
        {
            Renderer::WorldRenderer::render(*this);
        }

        void World::addEntity(std::shared_ptr<Entities::Entity> entity)
        {
            entities_[entity->ID] = entity;
        }

        void World::removeEntity(unsigned int ID)
        {
#ifndef NDEBUG
            if (entities_.find(ID) == entities_.end())
            logError("The entity(ID: " << ID << ") does not exist.");
#endif
            entities_.erase(ID);
        }

        std::shared_ptr<Entities::Entity> World::getEntity(unsigned int ID)
        {
#ifndef NDEBUG
            if (entities_.find(ID) == entities_.end())
            logError("The entity(ID: " << ID << ") does not exist.");
#endif
            return entities_[ID];
        }

        void World::tick()
        {
            player->move(0.1f, terrain);
            if (twoD)
            {
                //Cast the terrain
                auto *castedTerrain = (Terrain::TwoDTerrain *) terrain;
                castedTerrain->tick(player);
            }
        }

        const std::map<unsigned int, std::shared_ptr<Entities::Entity>> &World::getEntities() const
        {
            return entities_;
        }

        bool World::isTwoD() const
        {
            return twoD;
        }
    }
}