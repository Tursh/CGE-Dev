/*
 * Player.cpp
 *
 * Created by tursh on 10/15/20.
*/

#include "Entities/Player.h"
#include <glm/vec2.hpp>

#define _USE_MATH_DEFINES

#include <cmath>
#include <Loader/Meshes/TwoDAnimatedMesh.h>
#include <GUI/Text/TextRenderer.h>
#include <Utils/Log.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>
#include <Utils/PerlinNoise.h>

#include "IO/Input.h"

namespace CGE::Entities
{
    const glm::vec3 PLAYER_SIZE = {0.9f, 1.8f, 0.9f};

    Player::Player(unsigned int texMeshID, CGE::View::Camera &camera)
            : Entity(texMeshID, glm::vec3(0, 0, 0.1f), glm::vec3(0.7853f * 2, 0, 0)), camera_(camera) {}

    Player::Player(CGE::Loader::TexturedMesh *texMesh, CGE::View::Camera &camera, glm::vec3 position,
                   glm::vec3 rotation)
            : Entity(std::shared_ptr<CGE::Loader::TexturedMesh>(texMesh), position, rotation),
              camera_(camera) {}

    void Player::move(float speed)
    {

        //We start with a 3D vector of (0, 0, 0)
        glm::vec3 relativeForces(0);

        //If there is a opened panel, rotate camera depending on the mouse forces
        if (!CGE::IO::input::isPanelVisible())
        {
            //Get mouse input
            glm::vec2 mouse = CGE::IO::input::getCursorShifting();
            rotate({-mouse.y, mouse.x, 0});


            //Get key inputs
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_W))
                relativeForces.z -= 1;
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_S))
                relativeForces.z += 1;
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_A))
                relativeForces.x -= 1;
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_D))
                relativeForces.x += 1;
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
                relativeForces.y -= 1;
            if (CGE::IO::input::isKeyPressed(GLFW_KEY_SPACE))
                relativeForces.y += 1;
            //if (CGE::IO::input::isKeyPressed(GLFW_KEY_SPACE) && isOnGround())
            //{
            //    glm::vec3 speed = getSpeed();
            //    speed.y = 0;
            //    setSpeed(speed);
            //    addForce(3, glm::vec3(0, 0.2f, 0));
            //}

        }



        //Normalize the relative forces so that the speed is the same in all orientations
        if (!(glm::length(relativeForces) < 0.0001f))
            relativeForces = glm::normalize(relativeForces);

        relativeForces *= speed * (CGE::IO::input::isKeyPressed(GLFW_KEY_LEFT_CONTROL) ? 2.0f : 1.0f);

        //Orientate the forces
        glm::vec3 ar = getRenderRotation();

        auto s = (float) sin((double) ar.y);
        auto c = (float) cos((double) ar.y);

        glm::vec3 forces = relativeForces;

        forces.z = relativeForces.x * s + relativeForces.z * c;
        forces.x = relativeForces.x * c - relativeForces.z * s;

        addForce(1, forces);

    }

    const glm::vec3 &Player::getSize()
    {
        return PLAYER_SIZE;
    }
}