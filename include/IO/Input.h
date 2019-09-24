#pragma once

#include <GUI/Panel.h>
#include <GLFW/glfw3.h>                    //GLFW*
#include <glm/ext/vector_float2.hpp>    //glm::vec2

namespace CGE::IO::input
{

    /**
     * @param key: key to check (GLFW_KEY_<key>)
     * @return if the key is pressed
     */
    bool isKeyPressed(int key);

    /**
     * @param button: button to check (GLFW_BUTTON_MOUSE_<button>)
     * @return if the button on the mouse is pressed
     */
    bool isButtonPressed(int button);

    /**
     * Check if there is a visible panel
     */
    bool isPanelVisible();

    void addPanel(GUI::Panel *newPanel);

    void removePanel(GUI::Panel *panel);

    /**
     * Set your own Key callback
     * @param keyCallBack: void keycallback(GLFWwindow *, int key, int action)
     */
    void setYourOwnKeyCallBack(std::function<void(GLFWwindow *, int, int)> keyCallBack);

    void resetKeyCallBack();

    /**
     * Set your own mouse button callback
     * @param keyCallBack: void keycallback(GLFWwindow *, int key, int action)
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

    void toggleGrabMouse();

    void grabMouse();

    void ungrabMouse();
}
