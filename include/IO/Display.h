#pragma once

#include <GLFW/glfw3.h>

namespace CGE
{
    namespace IO
    {

        extern const unsigned int DEFAULT_WIDTH, DEFAULT_HEIGHT;

        //Create a dynamic window
        struct Display
        {
            unsigned int width, height, ID;
            //The window pointer
            GLFWwindow *window;

            //Create the window taking the name, default width and height
            Display(const char *name, unsigned int width, unsigned int, bool resizable = true);

            //Look for inputs changes and swap the drawing buffer
            void update() const;

            //Destroy the window
            ~Display();
        };

        //Get the display by ID (The first display ID is 0)
        Display *getDisplay(unsigned int ID = 0);

        /*
         Set your own MouseButton callback
         */
        void setYourOwnWindowResizeCallback(void(*windowResizeCallback)(int width, int height));


        void resetWindowResizeCallback();

    }
}
