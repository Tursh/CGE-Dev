//
// Created by tursh on 1/11/19.
//

#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/mat4x4.hpp>
#include <World/Entities/Player.h>

namespace CGE
{
    namespace Entities
    {
        class Player;
    }
    namespace View
    {
        struct Camera
        {
        public:
            glm::vec3 position_;
            glm::vec3 rotation_;
            bool firstPerson_;

            explicit Camera(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), bool firstPerson = true);

            glm::mat4 toViewMatrix(Entities::Player *player);
        };

    }
}

