#pragma once

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <functional>

namespace CGE::IO
{

    extern const unsigned int DEFAULT_WIDTH, DEFAULT_HEIGHT;

    //Create a dynamic window
    class Window
    {
        unsigned int width,
                height,
                ID;

        glm::mat4 projectionMatrix;

        //Projection matrix info
        float FOV = 45.0f, zNear = 0.000001f, zFar = 100.0f;

        //The window pointer
        GLFWwindow *glfwWindow_;

    public:

        //Look for inputs changes and swap the drawing buffer
        void update() const;

        bool shouldClose();

        //Create the window taking the name, default width and height
        Window(const char *name, unsigned int width, unsigned int, bool resizable = true);

        //Destroy the window
        ~Window();

        void setDimension(glm::ivec2 dimension);

        unsigned int getWidth() const;

        unsigned int getHeight() const;

        unsigned int getID() const;

        void createProjectionMatrix(float FOV, float zNear = 0.000001f, float zFar = 100.0f);

        const glm::mat4 &getProjectionMatrix() const;

        GLFWwindow *getGlfwWindow() const;
    };

    //Get the display by ID (The first display ID is 0)
    Window *getWindow(unsigned int ID = 0);

    /**
     *
     * @param callback
     */
    void setWindowResizeCallback(std::function<void(int, int)> callback);

    /**
     * Remove all the added window resize callback functions
     */
    void removeWindowResizeCallback();

}
