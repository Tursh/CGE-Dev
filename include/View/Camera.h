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

        explicit Camera(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));

        void followPlayer(Entities::Entity *player);

        glm::mat4 toViewMatrix(bool zAxis = true);

        /**
         * Get the normalized vector of where the camera is oriented at
         * @return the normalize vector of the camera orientation
         */
        glm::vec3 getRotationInNormalizedVector();
    };

}

