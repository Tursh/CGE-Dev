//
// Created by tursh on 1/17/19.
//

#include <Loader/RessourceManager.h>
#include <Entities/Entity.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Utils/TimeUtils.h>


namespace CGE::Entities
    {
        unsigned int futurID = 1;

        Entity::Entity(unsigned int texModelID, Loader::TexturedModelType type, glm::vec3 position, glm::vec3 rotation,
                       bool visible, bool movable)
                : ID(futurID), position_(position), rotation_(rotation), visible_(visible), movable_(movable)
        {
            switch (type)
            {
                case Loader::Basic2DTexturedModel:
                    texModel_ = CGE::Loader::resManager::getTexModel(texModelID);
                    break;
                case Loader::Basic3DTexturedModel:
                    texModel_ = CGE::Loader::resManager::getTexModel(texModelID);
                    break;
                case Loader::Animated2DModel:
                    texModel_ = CGE::Loader::resManager::getFlat2DAnimation(texModelID);
                    break;
                case Loader::Animated3DModel:break;
            }
            futurID++;
            size_ = texModel_->getModelSize();
        }

        Entity::Entity(Loader::TexturedModel *texModel, glm::vec3 position, glm::vec3 rotation, bool visible,
                       bool movable)
                : texModel_(texModel), ID(futurID), position_(position), rotation_(rotation), visible_(visible),
                  movable_(movable), size_(texModel_->getModelSize())
        {
            futurID++;
        }

        Entity::~Entity()
        {}

        void Entity::startAnimation(unsigned int ID)
        {
            texModel_->startAnimation(ID);
        }

        glm::vec3 Entity::getExactPosition()
        {
            return lastPosition_ + (position_ - lastPosition_) * CGE::Utils::getDelta();
        }

        glm::mat4 Entity::getTransformationMatrix()
        {
            glm::mat4 matrix(1);
            glm::vec3 position;
            glm::vec3 rotation;
            if (movable_)
            {
                float delta = Utils::getDelta();
                position = lastPosition_ + (position_ - lastPosition_) * delta;
                rotation = lastRotation_ + (rotation_ - lastRotation_) * delta;
            } else
            {
                position = position_;
                rotation = rotation_;
            }
            matrix = glm::translate(matrix, position);
            matrix = glm::rotate(matrix, -rotation.z, {0, 0, 1});
            matrix = glm::rotate(matrix, rotation.x, {1, 0, 0});
            matrix = glm::rotate(matrix, rotation.y, {0, 1, 0});

            if (texModel_->getType() == Loader::Animated2DModel)
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
