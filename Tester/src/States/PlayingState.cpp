
/*
 * PlayingState.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: tursh
 */

#include "PlayingState.h"

#include <IO/Input.h>
#include <glm/gtc/matrix_transform.hpp>
#include <IO/Display.h>
#include <Animation/Animator.h>
#include <Loader/RessourceManager.h>

namespace PlayingCallBacks
{
    void KeyCallBack(GLFWwindow *window, int key, int action);

    void MouseCallBack(GLFWwindow *window, int button, int action);
}

CGE::GUI::Button *button;

PlayingState::PlayingState()
        : player_(1, true), world(&player_), model(CGE::Loader::resManagement::getFlat2DAnimation(1))
{
    CGE::IO::input::setYourOwnKeyCallBack(PlayingCallBacks::KeyCallBack);
    CGE::IO::input::setYourOwnMouseButtonCallBack(PlayingCallBacks::MouseCallBack);

    glfwSetInputMode(CGE::IO::getDisplay()->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //world.addEntity(&player_);
    //Add the horse
    //world.addEntity(new CGE::Entities::Entity(1));

    button = new CGE::GUI::Button(CGE::GUI::DEFAULT, glm::vec2(0.0f, 0.0f), glm::vec2(0.5f, 0.2f), "HELLO", []()
    {});
    world.addEntity(new CGE::Entities::Entity(&model));
    //CGE::Loader::TwoDAnimatedModel animatedModel = CGE::Loader::resManagement::getFlat2DAnimation(1);
}

PlayingState::~PlayingState()
{
    delete button;
    //Unset the callbacks
    CGE::IO::input::resetKeyCallBack();
    CGE::IO::input::resetMouseButtonCallBack();
}


void PlayingState::tick(float delta)
{
    button->checkEvent();

    if (CGE::IO::input::isKeyPressed(GLFW_KEY_P))
    {
        model.startAnimation(1);
    }

    CGE::Animations::Animator::updateAnimations();

    if (glfwGetInputMode(CGE::IO::getDisplay()->window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
    {
        //Mouse input
        glm::vec2 mouseShifting = CGE::IO::input::getCursorShifting();
        player_.rotation_.y -= mouseShifting.x / 360;
        player_.rotation_.x -= mouseShifting.y / 360;
        if (-1.57f > player_.rotation_.x)
            player_.rotation_.x = -1.57f;

        if (player_.rotation_.x > 1.57)
            player_.rotation_.x = 1.57f;
    }
    player_.move(0.1f);

    //world.getEntity(2)->position_.z += 0.05f;

    //logInfo("rotation: " << camera->rotation_.y << " x: " << camera->position_.x << " y: " << camera->position_.y << " z: " << camera->position_.z);


}

void PlayingState::draw()
{
    //button->draw();
    world.render();
}

namespace PlayingCallBacks
{
    void KeyCallBack(GLFWwindow *window, int key, int action)
    {

        if (key == GLFW_KEY_G && action == GLFW_PRESS)
        {
            if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            else
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

    }

    void MouseCallBack(GLFWwindow *window, int button, int action)
    {

    }
}
