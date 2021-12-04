#include <utility>

//
// Created by tursh on 1/17/19.
//

#include <Loader/RessourceManager.h>
#include <Entities/Entity.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Utils/TimeUtils.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>


namespace CGE::Entities
{
    unsigned int futureID = 1;

    Entity::Entity(unsigned int texMeshID, glm::vec3 position,
                   glm::vec3 rotation,
                   bool visible)
            : ID_(futureID),
              ap_(position),
              op_(position),
              ar_(rotation),
              or_(rotation),
              texMesh_(CGE::Loader::resManager::getTexMesh(texMeshID)),
              visible_(visible)
    {
        //addForce(INT_MAX, {0, -0.04f, 0});
        ++futureID;
    }

    Entity::Entity(std::shared_ptr<Loader::TexturedMesh> texMesh, glm::vec3 position, glm::vec3 rotation,
                   bool visible)
            : texMesh_(std::move(texMesh)),
              ID_(futureID),
              ap_(position),
              op_(position),
              ar_(rotation),
              or_(rotation),
              visible_(visible)
    {
        //addForce(INT_MAX, {0, -0.04f, 0});
        ++futureID;
    }

    glm::vec3 Entity::getRenderPosition()
    {
        return op_ + (ap_ - op_) * CGE::Utils::TPSClock::getDelta();
    }


    glm::vec3 Entity::getRenderRotation()
    {
        return or_ + (ar_ - or_) * CGE::Utils::TPSClock::getDelta();
    }

    glm::mat4 Entity::getTransformationMatrix()
    {
        glm::mat4 matrix(1);
        glm::vec3 position = getRenderPosition();
        glm::vec3 rotation = getRenderRotation();

        matrix = glm::translate(matrix, position);
        matrix = glm::rotate(matrix, rotation.x, {1, 0, 0});
        matrix = glm::rotate(matrix, rotation.y, {0, 1, 0});
        matrix = glm::rotate(matrix, rotation.z, {0, 0, 1});

        if (!texMesh_->isThreeDimension())
        {
            glm::vec2 modelSize = texMesh_->getTextureSize();
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

    void Entity::rotate(glm::vec3 rotation)
    {
        ar_ += rotation;
    }

    void Entity::update()
    {
        op_ = ap_;
        or_ = ar_;
        os_ = as_;
        oa_ = aa_;

        //Acceleration
        //Get acceleration from the forces
        aa_ = glm::vec3(0);
        auto it = forces_.begin();
        while (it != forces_.end())
        {
            //Add force to player acceleration
            aa_ += std::get<1>(*it);
            //Check duration
            int &duration = std::get<0>(*it);
            --duration;
            if (duration == 0)
                forces_.erase(it);
            else
                ++it;
        }

        //Speed
        //Add acceleration to speed
        as_ += aa_;
        //Natural deceleration
        as_ *= 0.9f;

        //Position
        ap_ += as_;
        if (checkCollision_ != nullptr)
        {
            ap_ = checkCollision_(this);
        }

    }

    void Entity::render()
    {
        if (visible_)
            texMesh_->render();
    }

    void Entity::addForce(int duration, glm::vec3 Size)
    {
        forces_.emplace_back(duration, Size);
    }

    const unsigned int &Entity::getID() const { return ID_; }

    bool Entity::isOnGround() { return fabsf(ap_.y - op_.y) < 0.0001f; }

    bool Entity::isVisible() const { return visible_; }

    void Entity::setVisible(bool visible) { visible_ = visible; }

    const glm::vec3 &Entity::getOldPosition() const { return op_; }

    const glm::vec3 &Entity::getOldRotation() const { return or_; }

    const glm::vec3 &Entity::getPosition() const { return ap_; }

    const glm::vec3 &Entity::getRotation() const { return ar_; }

    const glm::vec3 &Entity::getSpeed() const { return as_; }

    void Entity::setSpeed(const glm::vec3 &speed) { as_ = speed; }

    const Loader::SharedTexMesh &Entity::getTexMesh() const { return texMesh_; }

    void Entity::setTexMesh(const std::shared_ptr<Loader::TexturedMesh> &texMesh) { texMesh_ = texMesh; }

    void Entity::setCollisionFunc(const std::function<glm::vec3(Entity *)> &collisionFunc)
    {
        checkCollision_ = collisionFunc;
    }

    static const glm::vec3 zero(0);

    const glm::vec3 &Entity::getSize() { return texMesh_ != nullptr ? texMesh_->getMeshSize() : zero; }

    Physics::BoxCollider Entity::getBoxCollider()
    {
        glm::vec3 size = getSize();
        return Physics::BoxCollider(op_.x - size.x / 2, op_.x + size.x / 2, op_.y - size.y / 2, op_.y + size.y / 2,
                      op_.z - size.z / 2, op_.z + size.z / 2);
    }

    bool Entity::shouldDie()
    {
        return false;
    }

}
