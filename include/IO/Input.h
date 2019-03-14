#pragma once

#include <GLFW/glfw3.h>                    //GLFW*
#include <glm/ext/vector_float2.hpp>    //glm::vec2
#include <GUI/Panel.h>

namespace CGE
{
    namespace IO
    {
        namespace input
        {

            /*Initialize inputs*/
            void init();

            /*
             Return if the key on the keyboard is pressed
             key: key pressed (GLFW_KEY_<key>)
             */
            bool isKeyPressed(int key);

            /*
             Return if the button on the mouse is pressed
             button: button pressed (GLFW_BUTTON_MOUSE_<button>)
             */
            bool isButtonPressed(int button);

            //Check if there is a visible panel
            bool isPanelVisible();

            void addPanel(GUI::Panel *newPanel);

            void removePanel(GUI::Panel *panel);

            /*
             Set your own Key callback
             Caution: if used, isKeyPressed is useless
             */
            void setYourOwnKeyCallBack(void(*keyCallBack)(GLFWwindow *window, int key, int action));

            void resetKeyCallBack();

            /*
             Set your own MouseButton callback
             */
            void setYourOwnMouseButtonCallBack(void(*mouseButtonCallBack)(GLFWwindow *window, int button, int action));


            void resetMouseButtonCallBack();

            /*Get cursor position*/
            glm::vec2 getCursorPos(int displayID = -1);

            /*Return the movement of the mouse since the last call*/
            glm::vec2 getCursorShifting();

            namespace CallBacks
            {
                //Default callback for isKeyPressed
                void keyCallback(GLFWwindow *window, int key, int scancode,
                                 int action, int mode);

                //Default callback for  isButtonPressed
                void mouseButtonCallback(GLFWwindow *window, int button,
                                         int action, int mode);

                void mouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
            }

            glm::vec2 getMouseScroll();
        }
    }
}
