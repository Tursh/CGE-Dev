#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <IO/Window.h>
#include <IO/Input.h>
#include <Loader/RessourceManager.h>
#include <Utils/Log.h>
#include <GUI/GUIManager.h>

namespace CGE::IO::input
{
    void init();
}

namespace CGE
{

    IO::Window *display;

    IO::Window *initEngine(const char *name, unsigned int width, unsigned int height, bool resizable = true)
    {

        //Initialize GLFW
        if (!glfwInit())
        {
            logError("GLFW could not init");
            exit(-1);
        }

        //Create display
        display = new IO::Window(name, width, height, resizable);
        //Initialize GLEW
        if (glewInit() != GLEW_OK)
        {
            glfwTerminate();
            logError("GLEW could not initialize");
            exit(-1);
        }

        //init inputs
        IO::input::init();

        //init resource manager
        Loader::resManager::init();

        GUI::GUIManager::init();

#ifndef NDEBUG
        logInfo("The Game Engine was initialized correctly");
#endif

        return display;
    }

    void stopEngine()
    {
        CGE::GUI::GUIManager::terminate();
        Loader::resManager::terminate();
        delete display;
        glfwTerminate();
    }

    //TODO: 3D Animation
    //TODO: Shadow

}
