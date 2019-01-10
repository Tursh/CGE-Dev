
/*
 * PlayingState.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: tursh
 */

#include "PlayingState.h"

#include <IO/Input.h>
#include <Text/TextRenderer.h>
#include <Utils/Log.h>
#include <Utils/TimeUtils.h>
#include <Loader/RessourceManager.h>
#include <Shader/ModelShader/BasicShader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <IO/Display.h>

namespace PlayingCallBacks
{
    void KeyCallBack(GLFWwindow *window, int key, int action);

    void MouseCallBack(GLFWwindow *window, int button, int action);
}

CGE::Shader::BasicShader* basicShader;


PlayingState::PlayingState()
{
    CGE::IO::input::setYourOwnKeyCallBack(PlayingCallBacks::KeyCallBack);
    CGE::IO::input::setYourOwnMouseButtonCallBack(PlayingCallBacks::MouseCallBack);

    basicShader = new CGE::Shader::BasicShader;

    CGE::IO::Display* display = CGE::IO::getDisplay();
    basicShader->start();
    //basicShader->loadMatrix(CGE::Shader::PROJECTION, glm::mat4(1));
    basicShader->loadMatrix(CGE::Shader::PROJECTION, glm::perspective(45.0f, (float)display->width / display->height, 0.1f, 100.f));
    basicShader->stop();

}

glm::mat4 transMatrix(1);
glm::mat4 viewMatrix(1);

PlayingState::~PlayingState()
{
    //Unset the callbacks
    CGE::IO::input::resetKeyCallBack();
    CGE::IO::input::resetMouseButtonCallBack();
}



void PlayingState::tick(float delta)
{
}

glm::mat4 trans (1);

void PlayingState::draw()
{

    glEnable(GL_DEPTH_TEST);
    basicShader->start();
    transMatrix = glm::translate(transMatrix, glm::vec3(0.0f, 0.00f, 0.0f));
    basicShader->loadMatrix(CGE::Shader::TRANSFORMATION, transMatrix);
    basicShader->loadMatrix(CGE::Shader::VIEW, viewMatrix);
    CGE::Loader::resManagement::getTexModel(1).render();
    basicShader->stop();
    glDisable(GL_DEPTH_TEST);

}

namespace PlayingCallBacks
{
    void KeyCallBack(GLFWwindow *window, int key, int action)
    {
        if(key == GLFW_KEY_W)
        {
            viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, 1.0f));
        }
        if(key == GLFW_KEY_S)
        {
            viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, -1.0f));
        }
        if(key == GLFW_KEY_A)
        {
            viewMatrix = glm::translate(viewMatrix, glm::vec3(1.0f, 0, 0));
        }
        if(key == GLFW_KEY_D)
        {
            viewMatrix = glm::translate(viewMatrix, glm::vec3(-1.0f, 0, 0));
        }
        if(key == GLFW_KEY_SPACE)
        {
            viewMatrix = glm::translate(viewMatrix, glm::vec3(0, -1.0f, 0));
        }
        if(key == GLFW_KEY_LEFT_SHIFT)
        {
            viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 1.0f, 0));
        }

    }

    void MouseCallBack(GLFWwindow *window, int button, int action)
    {

    }
}
