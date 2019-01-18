//
// Created by tursh on 1/17/19.
//

#include <glm/vec2.hpp>
#include <cmath>

#include "Entities/Player.h"
#include "IO/Input.h"

namespace CGE
{
    namespace Entities
    {

        void Player::move(float speed)
        {
            glm::vec3 movement(0);
            //Key input
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_W))
            {
                movement.z -= 1;
            }
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_S))
            {
                movement.z += 1;
            }
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_A))
            {
                movement.x -= 1;
            }
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_D))
            {
                movement.x += 1;
            }
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_SPACE))
            {
                movement.y += 1;
            }
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
            {
                movement.y -= 1;
            }

            position_.y += movement.y * speed;

            float dist = movement.z * movement.z + movement.x * movement.x;
            if (dist < 0.01f)
                return;

            dist = speed / sqrt(dist);

            movement *= dist;

            auto s = (float) sin((double) rotation_.y);
            auto c = (float) cos((double) rotation_.y);

            position_.x += movement.z * s + movement.x * c;
            position_.z += movement.z * c - movement.x * s;
        }
    }
}