//
// Created by tursh on 1/11/19.
//

#include <View/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace CGE
{
    namespace View
    {

        glm::mat4 Camera::toViewMatrix(Entities::Player *player)
        {
            glm::vec3 position;
            glm::vec3 rotation;
            if (firstPerson_)
            {
                position = player->position_ + glm::vec3(0, 1, 0);
                rotation = player->rotation_;
            } else
            {
                //TODO: When we scroll, it goes to third person view
            }
            float cosPitch = cos(rotation.x);
            float sinPitch = sin(rotation.x);
            float cosYaw = cos(rotation.y);
            float sinYaw = sin(rotation.y);

            glm::vec3 xaxis = {cosYaw, 0, -sinYaw};
            glm::vec3 yaxis = {sinYaw * sinPitch, cosPitch, cosYaw * sinPitch};
            glm::vec3 zaxis = {sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw};

            // Create a 4x4 view matrix from the right, up, forward and eye position vectors
            glm::mat4 viewMatrix = {
                    glm::vec4(xaxis.x, yaxis.x, zaxis.x, 0),
                    glm::vec4(xaxis.y, yaxis.y, zaxis.y, 0),
                    glm::vec4(xaxis.z, yaxis.z, zaxis.z, 0),
                    glm::vec4(-dot(xaxis, position), -dot(yaxis, position), -dot(zaxis, position), 1)
            };

            return viewMatrix;
        }

        Camera::Camera(bool firstPerson)
                : firstPerson_(firstPerson) {}
    }
}