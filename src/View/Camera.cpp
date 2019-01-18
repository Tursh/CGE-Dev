//
// Created by tursh on 1/11/19.
//

#include <View/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace CGE
{
    namespace View
    {
        Camera::Camera(Entities::Player &player, bool firstPerson)
                : position_(0), rotation_(0), player_(player), firstPerson_(firstPerson) {}

        Camera::Camera(glm::vec3 position_, glm::vec3 rotation_, Entities::Player &player, bool firstPerson)
                : position_(position_), rotation_(rotation_), player_(player), firstPerson_(firstPerson) {}

        glm::mat4 Camera::toViewMatrix()
        {
            // I assume the values are already converted to radians.
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

            return viewMatrix;
        }

        void Camera::move()
        {
            if (firstPerson_)
            {
                //Set the camera at the top of the player (where the player head should be)
                position_ = player_.position_ + glm::vec3(0, 1, 0);
                rotation_ = player_.rotation_;
            } else
            {
                //TODO: When we scroll, it goes to third person view
            }
        }
    }
}