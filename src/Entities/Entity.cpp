#include <utility>

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

    Entity::Entity(unsigned int texModelID, glm::vec3 position,
                   glm::vec3 rotation,
                   bool visible)
            : ID_(futurID),
              ap_(position),
              op_(position),
              ar_(rotation),
              or_(rotation),
              texModel_(CGE::Loader::resManager::getTexModel(texModelID)),
              visible_(visible)
    {
        futurID++;
    }

    Entity::Entity(std::shared_ptr<Loader::TexturedModel> texModel, glm::vec3 position, glm::vec3 rotation,
                   bool visible)
            : texModel_(std::move(texModel)),
              ID_(futurID),
              ap_(position),
              op_(position),
              ar_(rotation),
              or_(rotation),
              visible_(visible)
    {
        futurID++;
    }

    glm::vec3 Entity::getPosition()
    {
        return op_ + (ap_ - op_) * CGE::Utils::getDelta();
    }


    glm::vec3 Entity::getRotation()
    {
        return or_ + (ar_ - or_) * CGE::Utils::getDelta();
    }

    glm::mat4 Entity::getTransformationMatrix()
    {
        glm::mat4 matrix(1);
        glm::vec3 position = getPosition();
        glm::vec3 rotation = getRotation();

        matrix = glm::translate(matrix, position);
        matrix = glm::rotate(matrix, rotation.x, {1, 0, 0});
        matrix = glm::rotate(matrix, rotation.y, {0, 1, 0});
        matrix = glm::rotate(matrix, rotation.z, {0, 0, 1});

        if (!texModel_->isThreeDimension())
        {
            glm::vec2 modelSize = texModel_->getTextureSize();
            matrix = glm::scale(matrix, {modelSize.x, modelSize.y, 1});
        }

        return matrix;
    }

    void Entity::move(glm::vec3 movement)
    {
        //Keep track of the older
        op_ = ap_;
        or_ = ar_;

        ap_ += movement;
    }

    void Entity::render()
    {
        if (visible_)
            texModel_->render();
    }

    void Entity::addForce(int duration, glm::vec3 Size)
    {
        forces_.emplace_back(duration, Size);
    }

    unsigned int Entity::getID() const
    {
        return ID_;
    }

    const std::shared_ptr<Loader::TexturedModel> &Entity::getTexModel() const
    {
        return texModel_;
    }

    bool Entity::isVisible() const
    {
        return visible_;
    }

    void Entity::setVisible(bool visible)
    {
        visible_ = visible;
    }

    void Entity::setTexModel(const std::shared_ptr<Loader::TexturedModel> &texModel)
    {
        texModel_ = texModel;
    }

}
