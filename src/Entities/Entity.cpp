//
// Created by tursh on 1/17/19.
//

#include <Loader/RessourceManager.h>
#include <Entities/Entity.h>
#include <glm/gtc/matrix_transform.hpp>
#include <hdf5_hl.h>
#include <Utils/TimeUtils.h>


namespace CGE
{
    namespace Entities
    {
        unsigned int futurID = 1;

        Entity::Entity(unsigned int texModelID, Loader::TexturedModelType type, glm::vec3 position, glm::vec3 rotation,
                       bool visible)
                : ID(futurID), position_(position), rotation_(rotation), visible_(visible)
        {
            switch (type)
            {
                case Loader::BasicTexturedModel:
                    texModel_ = CGE::Loader::resManagement::getTexModel(texModelID);
                    break;
                case Loader::Animated2DModel:
                    texModel_ = CGE::Loader::resManagement::getFlat2DAnimation(texModelID);
                    break;
            }
            futurID++;
        }

        Entity::Entity(Loader::TexturedModel *texModel, glm::vec3 position, glm::vec3 rotation, bool visible)
                : texModel_(texModel), ID(futurID), position_(position), rotation_(rotation), visible_(visible)
        {
            futurID++;
        }

        Entity::~Entity()
        {
            delete (texModel_);
        }

        void Entity::startAnimation(unsigned int ID)
        {
            texModel_->startAnimation(ID);
        }

        glm::vec3 Entity::getExactPosition()
        {
            return lastPosition_ + (position_- lastPosition_) * CGE::Utils::getDelta();
        }

        glm::mat4 Entity::getTransformationMatrix()
        {
            glm::mat4 matrix(1);
            float delta = Utils::getDelta();
            //logInfo(((position_ - lastPosition_) / delta).x);
            glm::vec3 position = lastPosition_ + (position_- lastPosition_) * delta;
            glm::vec3 rotation = lastRotation_ + (rotation_ - lastRotation_) * delta;
            matrix = glm::translate(matrix, position);
            matrix = glm::rotate(matrix, -rotation.z, {0, 0, 1});
            matrix = glm::rotate(matrix, rotation.x, {1, 0, 0});
            matrix = glm::rotate(matrix, rotation.y, {0, 1, 0});

            if(texModel_->getType() == Loader::Animated2DModel)
            {
                glm::vec2 modelSize = texModel_->getModelSize();
                matrix = glm::scale(matrix, glm::vec3(modelSize.x, modelSize.y, 0));
            }

            return matrix;
        }

        void Entity::move(glm::vec3 movement)
        {
            //Keep track of the older
            lastPosition_ = position_;
            lastRotation_ = rotation_;

            position_ += movement;
        }

        void Entity::render()
        {
            if (visible_)
                texModel_->render();
        }
    }
}