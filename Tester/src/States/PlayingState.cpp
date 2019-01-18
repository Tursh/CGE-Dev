
/*
 * PlayingState.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: tursh
 */

#include "PlayingState.h"

#include <IO/Input.h>
#include <Loader/RessourceManager.h>
#include <Shader/ModelShader/BasicShader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <IO/Display.h>

namespace PlayingCallBacks
{
    void KeyCallBack(GLFWwindow *window, int key, int action);

    void MouseCallBack(GLFWwindow *window, int button, int action);
}

CGE::Shader::BasicShader *basicShader;

PlayingState::PlayingState()
        : player_(), camera_(player_)
{
    CGE::IO::input::setYourOwnKeyCallBack(PlayingCallBacks::KeyCallBack);
    CGE::IO::input::setYourOwnMouseButtonCallBack(PlayingCallBacks::MouseCallBack);

    basicShader = new CGE::Shader::BasicShader;

    CGE::IO::Display *display = CGE::IO::getDisplay();
    basicShader->start();
    //basicShader->loadMatrix(CGE::Shader::PROJECTION, glm::mat4(1));
    basicShader->loadMatrix(CGE::Shader::PROJECTION,
                            glm::perspective(45.0f, (float) display->width / display->height, 0.1f, 100.f));
    basicShader->stop();

    glfwSetInputMode(display->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

PlayingState::~PlayingState()
{
    //Unset the callbacks
    CGE::IO::input::resetKeyCallBack();
    CGE::IO::input::resetMouseButtonCallBack();
}


void PlayingState::tick(float delta)
{


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
    camera_.move();

    //logInfo("rotation: " << camera->rotation_.y << " x: " << camera->position_.x << " y: " << camera->position_.y << " z: " << camera->position_.z);
}

void PlayingState::draw()
{

    glEnable(GL_DEPTH_TEST);
    basicShader->start();
    transMatrix = glm::translate(transMatrix, glm::vec3(0.0f, 0.00f, 0.0f));
    basicShader->loadMatrix(CGE::Shader::TRANSFORMATION, transMatrix);
    basicShader->loadMatrix(CGE::Shader::VIEW, camera_.toViewMatrix());
    CGE::Loader::resManagement::getTexModel(1).render();
    basicShader->stop();
    glDisable(GL_DEPTH_TEST);

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
