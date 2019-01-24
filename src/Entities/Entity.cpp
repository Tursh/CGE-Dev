//
// Created by tursh on 1/17/19.
//

#include <Loader/RessourceManager.h>
#include <World/Entities/Entity.h>
#include <glm/gtc/matrix_transform.hpp>


namespace CGE
{
    namespace Entities
    {
        unsigned int futurID = 1;

        void Entity::render()
        {
            if (visible_)
                texModel_.render();
        }

        Entity::Entity(unsigned int texModelID, glm::vec3 position, glm::vec3 rotation, bool visible)
                : texModel_(CGE::Loader::resManagement::getTexModel(texModelID)), ID(futurID), position_(position),
                  rotation_(rotation), visible_(visible)
        {
            futurID++;
        }

        Entity::Entity(Loader::TexturedModel texModel, glm::vec3 position, glm::vec3 rotation, bool visible)
                : texModel_(texModel), ID(futurID), position_(position), rotation_(rotation), visible_(visible)
        {
            futurID++;
        }

        glm::mat4 Entity::getTransformationMatrix()
        {
            glm::mat4 matrix(1);
            matrix = glm::translate(matrix, position_);
            matrix = glm::rotate(matrix, rotation_.x, {1, 0, 0});
            matrix = glm::rotate(matrix, rotation_.y, {0, 1, 0});
            matrix = glm::rotate(matrix, rotation_.z, {0, 0, 1});

            return matrix;
        }
    }
}