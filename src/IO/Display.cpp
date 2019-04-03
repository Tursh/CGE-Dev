#include <GL/glew.h>    //glViewPort
#include <IO/Display.h>    //Display::
#include <Utils/Log.h>        //logError
#include <GUI/GUIManager.h>
#include <Utils/TimeUtils.h>
#include <map>
#include <glm/ext/matrix_clip_space.hpp>
#include <Text/TextRenderer.h>
#include <Loader/RessourceManager.h>

namespace CGE
{
    namespace IO
    {

        const unsigned int DEFAULT_WIDTH = 720, DEFAULT_HEIGHT = 720;

        unsigned int displayCreated = 0;
        std::map<unsigned int, Display *> displays;

        Display *getDisplay(unsigned int ID)
        {
#ifndef NDEBUG
            //Check if the display exists
            if (displays.find(ID) == displays.end())
            logError("There is no display with the ID: " << ID);
#endif
            return displays[ID];
        }

        void (*customWindowResizeCallback)(int, int);

        void setYourOwnWindowResizeCallback(void (*windowResizeCallback)(int, int))
        {
            customWindowResizeCallback = windowResizeCallback;
        }

        void resetWindowResizeCallback()
        {
            customWindowResizeCallback = nullptr;
        }

        void windowResizeCallback(GLFWwindow *win, int width, int height)
        {
            if (customWindowResizeCallback != nullptr)
                customWindowResizeCallback(width, height);
            glm::ivec2 newResolution(width, height);
            GUI::GUIManager::resetDisplayRes(newResolution);
            Text::textRenderer::resetDisplayResolution(newResolution);
            glViewport(0, 0, width, height);
            for (size_t i = 0; i < displays.size(); i++)
                if (displays[i]->window == win)
                {
                    displays[i]->width = static_cast<unsigned int>(width);
                    displays[i]->height = static_cast<unsigned int>(height);
                    displays[i]->projectionMatrix = glm::perspective(45.0f, (float) width / height, 0.00001f, 100.f);
                }
        }

        /*Initialize GLFW, the window and GL context*/
        Display::Display(const char *name, unsigned int width,
                         unsigned int height, bool resizable)
                : width(width), height(height), ID(displayCreated++),
                  projectionMatrix(glm::perspective(45.0f, (float) width / height, 0.00001f, 100.f))
        {
            //Set if resizable
            glfwWindowHint(GLFW_RESIZABLE, resizable);

            //Create window
            window = glfwCreateWindow(width, height, name, nullptr, nullptr);

            //Check if the window exists
            if (!window)
            {
                glfwTerminate();
                logError("[ERROR] GLFW could not create a window");
                exit(-1);
            }

            //Make the window context current
            glfwMakeContextCurrent(window);
            //Set the max fps to 60 (vsync)
            glfwSwapInterval(1);
            //set the color that the screen clear after draw
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            //Set the callback for when the user change the window size
            glfwSetWindowSizeCallback(window, windowResizeCallback);
            //Insert the new display created in the display list
            displays.insert(std::make_pair(ID, this)); // @suppress("Invalid arguments")
        }

        void Display::update() const
        {
            //Swap the drawing buffers
            glfwSwapBuffers(Display::window);
            //Check for events
            glfwPollEvents();
            //Clear the frame
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //Add to frame count
            Utils::addFrame();
            //Check if some resources are to clear
            Loader::resManager::clear();
        }

        Display::~Display()
        {
            //Remove from the display list
            displays.erase(ID);
            //Destroy the display
            glfwDestroyWindow(window);
        }

    }
}

/*
 TODO Optimisation
 TODO Report error only if DEBUG == 1
 */
