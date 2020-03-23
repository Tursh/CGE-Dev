#pragma once

#include <GUI/Panel.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>

namespace CGE::IO::input
{

    //---------- Keyboard Input ------------//

    /**
     * @param key: key to check (GLFW_KEY_<key>)
     * @return if the key is pressed
     */
    bool isKeyPressed(int key);

    /**
     * Set your own Key callback
     * @param keyCallBack: void keyCallback(GLFWwindow *, int key, int action)
     */
    void setYourOwnKeyCallBack(const std::function<void(GLFWwindow *, int, int)>& keyCallback);

    /**
     * Remove all custom key callbacks
     */
    void resetKeyCallBacks();



    //------------ Mouse Input -------------//

    /**
     * @param button: button to check (GLFW_BUTTON_MOUSE_<button>)
     * @return if the button on the mouse is pressed
     */
    bool isButtonPressed(int button);

    /**
     * Add your own mouse button callback
     * @param keyCallBack: void keycallback(GLFWwindow *, int key, int action)
     */
    void addCustomMouseButtonCallBack(const std::function<void(GLFWwindow *, int, int)>& mouseButtonCallBack);

    /**
     * Remove all custom button callbacks
     */
    void resetMouseButtonCallBacks();

    /**
     * Get the cursor position relative to the bottom left corner of the window
     * @param windowID The window ID (Default : 0 -> first window created)
     * @param centerRelative Makes the position range (-1, -1) to (1, 1), the center begin (0, 0)
     * @return The cursor position
     */
    glm::vec2 getCursorPos(int windowID = 0, bool centerRelative = false);

    /**
     * The movement of the mouse since the last display update
     * @return the movement of the cursor
     */
    glm::vec2 getCursorShifting(bool inPixel = false);

    /**
     * @return Mouse scroll since last tick
     */
    glm::vec2 getMouseScroll();

    /**
     * Toggle the mouse grabbing
     */
    void toggleGrabMouse();

    /**
     * Grab the mouse
     */
    void grabMouse();

    /**
     * Ungrab the mouse
     */
    void ungrabMouse();


    //----------- Panel Input ----------//

    /**
     * Check if there is a visible panel
     */
    bool isPanelVisible();

    void addPanel(GUI::Panel *newPanel);

    void removePanel(GUI::Panel *panel);
}
