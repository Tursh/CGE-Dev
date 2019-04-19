#pragma once

#include <GLFW/glfw3.h>                    //GLFW*
#include <glm/ext/vector_float2.hpp>    //glm::vec2
#include <GUI/Panel.h>

namespace CGE::IO::input
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
    void setYourOwnKeyCallBack(std::function<void(GLFWwindow *, int, int)> keyCallBack);

    void resetKeyCallBack();

    /*
     Set your own MouseButton callback
     */
    void setYourOwnMouseButtonCallBack(std::function<void(GLFWwindow *, int, int)> mouseButtonCallBack);


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
