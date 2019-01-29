//
// Created by tursh on 1/17/19.
//

#include <glm/vec2.hpp>
#include <cmath>
#include <World/Entities/Player.h>
#include <Loader/Models/TwoDAnimatedModel.h>
#include <World/Terrain/TwoDTerrain.h>


#include "IO/Input.h"

namespace CGE
{
    namespace Entities
    {

        enum PlayerAnimationState
        {
            FRONT_IDLE = 0, FRONT_WALKING = 1, BACK_IDLE = 2, BACK_WALKING = 3, SIDE_IDLE = 4, SIDE_WALKING = 5
        };

        Player::Player(unsigned int texModelID, Loader::TexturedModelType type, bool twoD)
                : Entity(texModelID, type, glm::vec3(0, 0, 0.01f), glm::vec3(0), twoD),
                  camera_(new View::Camera((twoD) ? glm::vec3(0, 0, 10) : glm::vec3(0))),
                  twoD_(twoD) {}

        Player::Player(Loader::TexturedModel *texModel, bool twoD)
                : Entity(texModel),
                  camera_(new View::Camera((twoD) ? glm::vec3(0, 0, 10) : glm::vec3(0))),
                  twoD_(twoD) {}

        void Player::move(float speed, Terrain::Terrain *terrain)
        {
            if (!twoD_)
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
            } else
            {
                auto *aniModel = (Loader::TwoDAnimatedModel *) texModel_;
                auto *twoDTerrain = (Terrain::TwoDTerrain *) terrain;
                glm::vec2 movement(0);
                if (CGE::IO::input::isKeyPressed(GLFW_KEY_W))
                {
                    if (texModel_->getType() == Loader::Animated2DModel)
                    {
                        aniModel->startAnimation(BACK_WALKING);
                        aniModel->setIdleAnimation(BACK_IDLE);
                    }
                    movement.y += 1;
                }
                if (CGE::IO::input::isKeyPressed(GLFW_KEY_S))
                {
                    if (texModel_->getType() == Loader::Animated2DModel)
                    {
                        aniModel->startAnimation(FRONT_WALKING);
                        aniModel->setIdleAnimation(FRONT_IDLE);
                    }

                    movement.y -= 1;
                }
                if (CGE::IO::input::isKeyPressed(GLFW_KEY_A))
                {
                    if (texModel_->getType() == Loader::Animated2DModel)
                    {
                        aniModel->startAnimation(SIDE_WALKING);
                        aniModel->setIdleAnimation(SIDE_IDLE);
                        rotation_.y = 0;
                    }
                    movement.x -= 1;
                }
                if (CGE::IO::input::isKeyPressed(GLFW_KEY_D))
                {
                    if (texModel_->getType() == Loader::Animated2DModel)
                    {
                        aniModel->startAnimation(5);
                        aniModel->setIdleAnimation(4);
                        rotation_.y = 3.1415926f;
                    }
                    movement.x += 1;
                }
                //If there was no movement
                if(glm::length(movement) < 0.0001f)
                    aniModel->stopAnimation();

                position_.x += movement.x * speed;
                position_.y += movement.y * speed;
            }
            logInfo(position_.x << ", " << position_.y << ", " << position_.z);
        }

        View::Camera *Player::getCamera()
        {
            return camera_;
        }

        bool Player::isTwoD()
        {
            return twoD_;
        }

    }
}