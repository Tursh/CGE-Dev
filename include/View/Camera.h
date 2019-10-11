//
// Created by tursh on 1/11/19.
//

#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/mat4x4.hpp>
#include <Entities/Entity.h>

namespace CGE::View
{
    struct Camera
    {
        glm::vec3 position_;
        glm::vec3 rotation_;

        /**
         * Camera constructor
         * @param position Start position
         * @param rotation Start orientation (pitch, yaw, roll)
         */
        explicit Camera(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));

        /**
         * Set the camera position and orientation as the player
         * @param player The player entity
         */
        void followPlayer(Entities::Entity *player);

        /**
         * Create a view matrix from the camera position and orientation
         * @param zAxis Use the z axis (roll axis) in the create of the view matrix
         * @return The view matrix
         */
        glm::mat4 toViewMatrix(bool zAxis = true);

        /**
         * Get the normalized vector of where the camera is oriented at
         * @return the normalize vector of the camera orientation
         */
        glm::vec3 getRotationInNormalizedVector();
    };

}

