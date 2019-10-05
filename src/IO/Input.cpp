#include <glm/detail/type_vec2.hpp>
#include <Utils/Log.h>                        //logError
#include <Utils/TimeUtils.h>
#include <GUI/GUIManager.h>
#include "IO/Input.h"
#include <IO/Window.h>

namespace CGE::IO::input
{

    static GLFWwindow *window;
    /*Keys and Button array*/
    static bool *keys;
    static bool *mouse;
    /*Last mouse position*/
    static glm::vec3 lastMousePos(0);
    static glm::vec3 lastScroll(0);

    static std::vector<GUI::Panel *> currentPanels;

    std::function<void(GLFWwindow *, int, int)> customKeyCallBack;
    std::function<void(GLFWwindow *, int, int)> customMouseButtonCallBack;

    /*Initialize inputs*/
    void init()
    {
        window = getWindow()->getGlfwWindow();
        keys = new bool[348];
        mouse = new bool[10];
        for (int i = 0; i < 348; i++)
            keys[i] = false;
        for (int i = 0; i < 10; i++)
            mouse[i] = false;
        glfwSetKeyCallback(window, CallBacks::keyCallback);
        glfwSetMouseButtonCallback(window, CallBacks::mouseButtonCallback);
        glfwSetScrollCallback(window, CallBacks::mouseScrollCallback);
    }

    namespace CallBacks
    {
        void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
        {
            if (key > 348)
            {
                logError(key << "is not listed as a key");
                return;
            }

            //Set key in buffer for isKeyPressed function
            if (action != GLFW_REPEAT)
                keys[key] = action;
            //Call custom key callback
            if (customKeyCallBack != nullptr && !isPanelVisible())
                customKeyCallBack(window, key, action);
            //Call panel key callbacks
            else if (isPanelVisible())
                for (auto &panel : currentPanels)
                    if (panel->getVisibility())
                        panel->keyCallback(key, action);
        }

        void mouseButtonCallback(GLFWwindow *window, int button, int action, int mode)
        {
            mouse[button] = action;
            if (customMouseButtonCallBack != nullptr && !isPanelVisible() && !CGE::GUI::GUIManager::isMouseInGUI())
                customMouseButtonCallBack(window, button, action);
        }

        void mouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
        {
            lastScroll += glm::vec3(xoffset, yoffset, 0);
        }
    }

    /*
     Return if the key on the keyboard is pressed
     key: key pressed (GLFW_KEY_<key>)
     */
    bool isKeyPressed(int key)
    {
        return keys[key];
    }

    /*
     Return if the button on the mouse is pressed
     button: button pressed (GLFW_BUTTON_MOUSE_<button>)
     */
    bool isButtonPressed(int button)
    {
        return mouse[button];
    }

    //Check if there is a visible panel
    bool isPanelVisible()
    {
        for (auto &panel : currentPanels)
        {
            if (panel->getVisibility())
                return true;
        }
        return false;
    }

    void addPanel(GUI::Panel *newPanel)
    {
        currentPanels.push_back(newPanel);
    }

    void removePanel(GUI::Panel *panel)
    {
        if (std::find(currentPanels.begin(), currentPanels.end(), panel) != currentPanels.end())
            currentPanels.erase(std::remove(currentPanels.begin(), currentPanels.end(), panel),
                                currentPanels.end());
    }

    void setYourOwnKeyCallBack(std::function<void(GLFWwindow *, int, int)> keyCallBack)
    {
        customKeyCallBack = std::move(keyCallBack);
    }

    void resetKeyCallBack()
    {
        customMouseButtonCallBack = nullptr;
    }

    void setYourOwnMouseButtonCallBack(std::function<void(GLFWwindow *, int, int)> mouseButtonCallBack)
    {
        customMouseButtonCallBack = std::move(mouseButtonCallBack);
    }

    void resetMouseButtonCallBack()
    {
        customMouseButtonCallBack = nullptr;
    }

    /*Get cursor position relative to the game window*/
    glm::vec2 getCursorPos(int displayID)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        if (displayID >= 0)
        {
            Window *display = getWindow(displayID);
            x = x / display->getWidth() * 2 - 1;
            y = -(y / display->getHeight() * 2 - 1);
        }
        return glm::vec2((float) x, (float) y);
    }

    /*Return the movement of the mouse since the last call*/
    glm::vec2 getCursorShifting()
    {
        const glm::vec2 mousePos = getCursorPos(0);
        glm::vec2 delta = mousePos - (glm::vec2) lastMousePos;
        int tickCount = Utils::TPSClock::getTickCount();
        if ((int) lastMousePos.z != tickCount)
            lastMousePos = glm::vec3(mousePos.x, mousePos.y, tickCount);
        return delta;
    }

    glm::vec2 getMouseScroll()
    {
        glm::vec2 scroll = lastScroll;
        int tickCount = Utils::TPSClock::getTickCount();
        if (tickCount != lastScroll.z)
            lastScroll = glm::vec3(0, 0, tickCount);
        return scroll;
    }

    static bool isMouseGrabed = false;

    void grabMouse()
    {
        isMouseGrabed = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void ungrabMouse()
    {
        isMouseGrabed = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void toggleGrabMouse()
    {
        if(isMouseGrabed)
            ungrabMouse();
        else
            grabMouse();
    }
}
