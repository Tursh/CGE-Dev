#include <utility>

#include <GL/glew.h>    //glViewPort
#include <IO/Window.h>    //Display::
#include <Utils/Log.h>        //logError
#include <GUI/GUIManager.h>
#include <Utils/TimeUtils.h>
#include <map>
#include <glm/ext/matrix_clip_space.hpp>
#include <GUI/Text/TextRenderer.h>
#include <Loader/RessourceManager.h>

namespace CGE::IO
{

    const unsigned int DEFAULT_WIDTH = 720, DEFAULT_HEIGHT = 480;

    static unsigned int windowsCreated = 0;
    static std::map<unsigned int, Window *> windows;

    Window *getWindow(unsigned int ID)
    {
#ifndef NDEBUG
        //Check if the display exists
        if (windows.find(ID) == windows.end())
        logError("There is no display with the ID: " << ID)
#endif
        return windows[ID];
    }


    //Window resize callback reference (Definition at the EOF)
    static void windowResizeCallback(GLFWwindow *win, int width, int height);


    //-------------- Window Methods ----------------//

    Window::Window(const char *name, unsigned int width,
                   unsigned int height, bool resizable)
            : width_(width), height_(height), ID_(windowsCreated++),
              projectionMatrix_(glm::perspectiveFov(FOV_, (float)width_, (float)height_, zNear_, zFar_))
    {
        //Set if resizable
        glfwWindowHint(GLFW_RESIZABLE, resizable);

        //Create window
        glfwWindow_ = glfwCreateWindow((int)width, (int)height, name, nullptr, nullptr);

        //Check if the window exists
        if (!glfwWindow_)
        {
            glfwTerminate();
            logError("GLFW could not create a window")
            exit(-1);
        }

        //Make the window context current
        glfwMakeContextCurrent(glfwWindow_);
        //Set the max fps to 60 (vsync)
        glfwSwapInterval(0);
        //set the color that the screen clear after draw
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        //Set the callback for when the user change the window size
        glfwSetWindowSizeCallback(glfwWindow_, windowResizeCallback);
        //Insert the new display created in the display list
        windows.insert(std::make_pair(ID_, this)); // @suppress("Invalid arguments")
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

        Loader::loadMeshes();
        //Check if some resources are ready to be scrapped
        Loader::resManager::scrap();
    }

    Window::~Window()
    {
        //Remove from the display list
        windows.erase(ID_);
        //Destroy the display
        glfwDestroyWindow(glfwWindow_);
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(glfwWindow_);
    }

    const unsigned int &Window::getWidth() const
    {
        return width_;
    }

    const unsigned int &Window::getHeight() const
    {
        return height_;
    }

    const unsigned int &Window::getID() const
    {
        return ID_;
    }

    const glm::mat4 &Window::getProjectionMatrix() const
    {
        return projectionMatrix_;
    }

    GLFWwindow *Window::getGLFWWindow() const
    {
        return glfwWindow_;
    }

    void Window::setDimension(glm::ivec2 dimension)
    {
        width_ = dimension.x;
        height_ = dimension.y;
        projectionMatrix_ = glm::perspectiveFov(FOV_, (float)width_, (float)height_, zNear_, zFar_);
    }

    void Window::modifyProjectionMatrix(float FOV, float zNear, float zFar)
    {
        this->FOV_ = FOV;
        this->zNear_ = zNear;
        this->zFar_ = zFar;
        projectionMatrix_ = glm::perspectiveFov(FOV_, (float)width_, (float)height_, zNear_, zFar_);
    }


    //--------------Resize callback ----------------//

    static std::vector<std::function<void(int, int)>> customWindowResizeCallbacks;

    /**
     * Default window resizing callback
     */
    static void windowResizeCallback(GLFWwindow *win, int width, int height)
    {
        if (!customWindowResizeCallbacks.empty())
            for(const auto& callback : customWindowResizeCallbacks)
            callback(width, height);
        glm::ivec2 newDimension(width, height);
        GUI::GUIManager::resetWindowDimension(newDimension);
        GUI::Text::TextRenderer::resetWindowDimension(newDimension);
        glViewport(0, 0, width, height);
        for (auto &pairedWindow : windows)
        {
            Window *window = pairedWindow.second;
            //Check if it is the resized window
            if (window->getGLFWWindow() == win)
            {
                window->setDimension(newDimension);
            }
        }
    }

    void setWindowResizeCallback(const std::function<void(int, int)>& callbackFunction)
    {
        customWindowResizeCallbacks.push_back(callbackFunction);
    }

    void removeWindowResizeCallback()
    {
        customWindowResizeCallbacks.clear();
    }

}

/*
 TODO Optimisation
 */
