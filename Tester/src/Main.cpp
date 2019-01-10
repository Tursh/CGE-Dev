/*
 * Main.cpp
 *
 *  Created on: Dec 18, 2018
 *      Author: tursh
 */

#include "States/PlayingState.h"
#include <Engine.h>
#include <GLFW/glfw3.h>
#include <IO/Display.h>
#include <IO/Input.h>
#include <State/StateManager.h>
#include <Text/TextRenderer.h>
#include <Utils/TimeUtils.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Utils/Log.h>

//#include <Utils/Log.h>

void init()
{
    CGE::initEngine("Game Engine Tester", 500, 625);
    CGE::Text::textRenderer::init("res/graphics/fonts/Archivo-Regular.ttf");
}

void loop()
{
    CGE::IO::Display *display = CGE::IO::getDisplay();
    CGE::State::stateManager::setCurrentState(new PlayingState);
    while (!glfwWindowShouldClose(display->window)
#ifndef NDEBUG
        && !CGE::IO::input::isKeyPressed(GLFW_KEY_ESCAPE)
#endif
            )
    {
        CGE::State::State *currentState = CGE::State::stateManager::getCurrentState();
        currentState->tick(CGE::Utils::getDelta());
        currentState->draw();
        display->update();
        //Set the info in the Title Bar
        glfwSetWindowTitle(display->window, (std::string("Game Engine Tester | FPS: ") + std::to_string(CGE::Utils::getFPS())).c_str());
    }
}

void close()
{

}

int main()
{
    init();
    loop();
    close();
    return 0;
}

