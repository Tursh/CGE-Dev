//
// Created by tursh on 1/11/19.
//

#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/mat4x4.hpp>
#include <Entities/Player.h>

namespace CGE
{
    namespace View
    {
        struct Camera
        {
        public:
            Entities::Player &player_;
            bool firstPerson_;

            glm::vec3 position_;
            glm::vec3 rotation_;

            explicit Camera(Entities::Player &player, bool firstPerson = true);

            Camera(glm::vec3 position_, glm::vec3 rotation_, Entities::Player &player, bool firstPerson);

            glm::mat4 toViewMatrix();

            void move();
        };

    }
}

