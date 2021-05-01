#pragma once

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <functional>
#include <Shader/ProjectionMatrix.h>

/**
 * @brief IO functions (Window and input)
 */
namespace CGE::IO
{

    extern const unsigned int DEFAULT_WIDTH, DEFAULT_HEIGHT;

    /**
     * @brief A dynamic window using GLFW
     */
    class Window
    {
        /**
         * Window parameters
         */
        unsigned int width_, height_, ID_;

		/**
		 * The projection matrix that all shaders refer to
		 */
        Shader::ProjectionMatrix projectionMatrix_;

        /**
         * The GLFW window
         */
        GLFWwindow *glfwWindow_;

    public:

        /**
         * Look for inputs changes, swap the drawing buffers and manage GPU resources
         */
        void update() const;

        /**
         * @return Should the display close
         */
        bool shouldClose();

        /**
         * Create the window taking the name, default width and height
         * @param name The window name
         * @param width Window width
         * @param height Window height
         * @param resizable Will the window be resizable
         */
        Window(const char *name, unsigned int width, unsigned int height, bool resizable = true);

        /**
         * Destroy the window
         */
        ~Window();

        /**
         * Change the window width and/or height
         * @param dimension Dimension vector (x = Width, y = Height)
         */
        void setDimension(glm::ivec2 dimension);

        /**
         * @return Current window width
         */
        [[nodiscard]] const unsigned int &getWidth() const;

        /**
         * @return Current window height
         */
        [[nodiscard]] const unsigned int &getHeight() const;

        /**
         * @return Window ID
         */
        [[nodiscard]] const unsigned int &getID() const;

        /**
         * @return The projection matrix reference to use in your shader program
         */
        [[nodiscard]] Shader::ProjectionMatrix &getProjectionMatrix();

        /**
         * @return The GLFW window that this window refers to
         */
        [[nodiscard]] GLFWwindow *getGLFWWindow() const;
    };

    /**
     * Get the window by ID (The first display ID is 0)
     * @param ID The window ID
     * @return The window pointer assigned to this ID
     */
    Window *getWindow(unsigned int ID = 0);

    /**
     * Set a custom resize callback
     * @param callback Your callback function
     */
    void setWindowResizeCallback(const std::function<void(int, int)>& callback);

    /**
     * Remove all the added custom resize callback functions
     */
    void removeWindowResizeCallback();

}
