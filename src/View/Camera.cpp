//
// Created by tursh on 1/11/19.
//

#include <View/Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <IO/Input.h>
#include <Utils/TimeUtils.h>

namespace CGE::View
{

    glm::mat4 Camera::toViewMatrix(bool zAxis)
    {
        /*
        float cosPitch = cos(rotation_.x);
        float sinPitch = sin(rotation_.x);
        float cosYaw = cos(rotation_.y);
        float sinYaw = sin(rotation_.y);

        glm::vec3 xaxis = {cosYaw, 0, -sinYaw};
        glm::vec3 yaxis = {sinYaw * sinPitch, cosPitch, cosYaw * sinPitch};
        glm::vec3 zaxis = {sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw};

        // Create a 4x4 view matrix from the right, up, forward and eye position vectors
        glm::mat4 viewMatrix = {
                glm::vec4(xaxis.x, yaxis.x, zaxis.x, 0),
                glm::vec4(xaxis.y, yaxis.y, zaxis.y, 0),
                glm::vec4(xaxis.z, yaxis.z, zaxis.z, 0),
                glm::vec4(-dot(xaxis, position_), -dot(yaxis, position_), -dot(zaxis, position_), 1)
        };
        */
        glm::mat4 viewMatrix(1);
        viewMatrix = glm::rotate(viewMatrix, rotation_.x, glm::vec3(1, 0, 0));
        viewMatrix = glm::rotate(viewMatrix, rotation_.y, glm::vec3(0, 1, 0));
        //if(zAxis)
        viewMatrix = glm::rotate(viewMatrix, rotation_.z, glm::vec3(0, 0, 1));
        viewMatrix = glm::translate(viewMatrix, -position_);
        return viewMatrix;
    }

    Camera::Camera(glm::vec3 position, glm::vec3 rotation)
            : position_(position), rotation_(rotation) {}

    void Camera::followPlayer(Entities::Entity *player)
    {
        //TODO : Change the follow player function for TheGame project
        //double hyp = position_.z / tan(rotation_.x);
        //position_.x = static_cast<float>(player->position_.x + sin(rotation_.z) * hyp);
        //position_.y = static_cast<float>(player->position_.y + cos(rotation_.z) * hyp);
        position_ = player->getPosition();
        rotation_ = player->getRotation();
    }


}