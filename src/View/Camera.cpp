//
// Created by tursh on 1/11/19.
//

#include <View/Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <IO/Input.h>

namespace CGE
{
    namespace View
    {

        glm::mat4 Camera::toViewMatrix(Entities::Player *player)
        {
            if (!player->isTwoD())
            {
                if (firstPerson_)
                {
                    position_ = player->position_ + glm::vec3(0, 1, 0);
                    rotation_ = player->rotation_;
                } else
                {
                    //TODO: When we scroll, it goes to third person view
                }
            } else
            {
                float scrolling = IO::input::getMouseScroll().y;

                position_.x = player->position_.x;
                position_.y = player->position_.y;
                position_.z -= scrolling * 0.05f;
            }
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

        Camera::Camera(glm::vec3 position, glm::vec3 rotation, bool firstPerson)
                : firstPerson_(firstPerson), position_(position), rotation_(rotation) {}



    }
}