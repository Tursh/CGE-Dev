#include <utility>

#include <GL/glew.h>    //glViewPort
#include <IO/Window.h>    //Display::
#include <Utils/Log.h>        //logError
#include <GUI/GUIManager.h>
#include <Utils/TimeUtils.h>
#include <map>
#include <glm/ext/matrix_clip_space.hpp>
#include <Text/TextRenderer.h>
#include <Loader/RessourceManager.h>

namespace CGE::IO
{

    const unsigned int DEFAULT_WIDTH = 720, DEFAULT_HEIGHT = 720;

    unsigned int windowsCreated = 0;
    std::map<unsigned int, Window *> windows;

    Window *getWindow(unsigned int ID)
    {
#ifndef NDEBUG
        //Check if the display exists
        if (windows.find(ID) == windows.end())
        logError("There is no display with the ID: " << ID);
#endif
        return windows[ID];
    }

    static void windowResizeCallback(GLFWwindow *win, int width, int height);

    /**/
    Window::Window(const char *name, unsigned int width,
                   unsigned int height, bool resizable)
            : width(width), height(height), ID(windowsCreated++),
              projectionMatrix(glm::perspective(45.0f, (float) width / height, 0.00001f, 100.f))
    {
        //Set if resizable
        glfwWindowHint(GLFW_RESIZABLE, resizable);

        //Create window
        glfwWindow_ = glfwCreateWindow(width, height, name, nullptr, nullptr);

        //Check if the window exists
        if (!glfwWindow_)
        {
            glfwTerminate();
            logError("GLFW could not create a window");
            exit(-1);
        }

        //Make the window context current
        glfwMakeContextCurrent(glfwWindow_);
        //Set the max fps to 60 (vsync)
        glfwSwapInterval(1);
        //set the color that the screen clear after draw
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        //Set the callback for when the user change the window size
        glfwSetWindowSizeCallback(glfwWindow_, windowResizeCallback);
        //Insert the new display created in the display list
        windows.insert(std::make_pair(ID, this)); // @suppress("Invalid arguments")
    }

    void Window::update() const
    {
        //Swap the drawing buffers
        glfwSwapBuffers(glfwWindow_);
        //Check for events
        glfwPollEvents();
        //Clear the frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Add to frame count
        Utils::addFrame();
        //
        Loader::loadModels();
        //Check if some resources are to clear
        Loader::resManager::scrap();
    }

    Window::~Window()
    {
        //Remove from the display list
        windows.erase(ID);
        //Destroy the display
        glfwDestroyWindow(glfwWindow_);
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(glfwWindow_);
    }

    unsigned int Window::getWidth() const
    {
        return width;
    }

    unsigned int Window::getHeight() const
    {
        return height;
    }

    unsigned int Window::getID() const
    {
        return ID;
    }

    const glm::mat4 &Window::getProjectionMatrix() const
    {
        return projectionMatrix;
    }

    GLFWwindow *Window::getGlfwWindow() const
    {
        return glfwWindow_;
    }

    void Window::setDimension(glm::ivec2 dimension)
    {
        width = dimension.x;
        height = dimension.y;
        projectionMatrix = glm::perspective(FOV, (float) width / height, zNear, zFar);
    }

    void Window::createProjectionMatrix(float FOV, float zNear, float zFar)
    {
        this->FOV = FOV;
        this->zNear = zNear;
        this->zFar = zFar;
        projectionMatrix = glm::perspective(FOV, (float) width / height, zNear, zFar);
    }

    static std::function<void(int, int)> customWindowResizeCallback;

    /**
     * Default window resizing callback
     */
    static void windowResizeCallback(GLFWwindow *win, int width, int height)
    {
        if (customWindowResizeCallback != nullptr)
            customWindowResizeCallback(width, height);
        glm::ivec2 newDimension(width, height);
        GUI::GUIManager::resetWindowDimension(newDimension);
        Text::textRenderer::resetWindowDimension(newDimension);
        glViewport(0, 0, width, height);
        for (auto &pairedWindow : windows)
        {
            Window *window = pairedWindow.second;
            //Check if it is the resized window
            if (window->getGlfwWindow() == win)
            {
                window->setDimension(newDimension);
            }
        }
    }

    void setWindowResizeCallback(std::function<void(int, int)> callbackFunction)
    {
        customWindowResizeCallback = std::move(callbackFunction);
    }

    void removeWindowResizeCallback()
    {
        customWindowResizeCallback = nullptr;
    }

}

/*
 TODO Optimisation
 TODO Report error only if DEBUG == 1
 */
