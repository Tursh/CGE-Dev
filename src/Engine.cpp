#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GUI/GUIRenderer.h>
#include <IO/Display.h>
#include <IO/Input.h>
#include <Loader/RessourceManager.h>
#include <Utils/Log.h>
#include <Renderer/WorldRenderer.h>

namespace CGE
{

    IO::Display *display;

    IO::Display *initEngine(const char *name, unsigned int width, unsigned int height, bool resizable = true)
    {

        //Initialize GLFW
        if (!glfwInit())
        {
            logError("GLFW could not init");
            exit(-1);
        }

        //Create display
        display = new IO::Display(name, width, height, resizable);
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
        Loader::resManagement::init();

        GUI::GUIRenderer::init();

        Renderer::WorldRenderer::init();

#ifndef NDEBUG
        logInfo("The Game Engine was initialized correctly");
#endif

        return display;
    }

    void stopEngine()
    {
        delete display;
        glfwTerminate();
    }

    //TODO: Animation
    //TODO: Terrain
    //TODO: Shadow

}
