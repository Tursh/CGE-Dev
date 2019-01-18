//
// Created by tursh on 1/17/19.
//

#include <Entities/Entity.h>
#include <Loader/RessourceManager.h>

namespace CGE
{
    namespace Entities
    {

        void Entity::render()
        {
            Loader::resManagement::getTexModel(ID).render();
        }
    }
}