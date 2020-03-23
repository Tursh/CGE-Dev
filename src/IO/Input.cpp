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

    static std::vector<GUI::Panel *> currentPanels;

    std::vector<std::function<void(GLFWwindow *, int, int)>> customKeyCallBacks;
    std::vector<std::function<void(GLFWwindow *, int, int)>> customMouseButtonCallBacks;

    //----------- Default Callbacks ---------//

    namespace CallBacks
    {
        //Default callback for isKeyPressed
        void keyCallback(GLFWwindow *window, int key, int scancode,int action, int mode);

        //Default callback for isButtonPressed
        void mouseButtonCallback(GLFWwindow *window, int button, int action, int mode);

        //Default callback for mouse scroll
        void mouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    }

    /*Initialize inputs*/
    void init()
    {
        window = getWindow()->getGLFWWindow();
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



    /*Get cursor position relative to the game window*/
    glm::vec2 getCursorPos(int windowID, bool centerRelative)
    {
        //Get the position
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        //Make it relative to the bottom left of the window
        Window *display = getWindow(windowID);
        y = display->getHeight() - y;

        //Make it center relative if needed
        if (centerRelative)
        {
            x = x / display->getWidth() * 2 - 1;
            y = y / display->getHeight() * 2 - 1;
        }

        return glm::vec2((float) x, (float) y);
    }


    /*Last mouse position*/
    static glm::vec3 lastMousePos;
    static glm::vec3 lastMousePixelPos;

    /*Return the movement of the mouse since the last call*/
    glm::vec2 getCursorShifting(bool inPixel)
    {
        const glm::vec2 mousePos = getCursorPos(0, !inPixel);
        glm::vec3 &lastMousePosition = inPixel ? lastMousePixelPos : lastMousePos;
        glm::vec2 delta = mousePos - (glm::vec2) lastMousePosition;
        int tickCount = Utils::TPSClock::getTickCount();
        if ((int) lastMousePosition.z != tickCount)
            lastMousePosition = glm::vec3(mousePos.x, mousePos.y, tickCount);
        return delta;
    }


    static glm::vec3 lastScroll;

    glm::vec2 getMouseScroll()
    {
        glm::vec2 scroll = lastScroll;
        int tickCount = Utils::TPSClock::getTickCount();
        if (tickCount != lastScroll.z)
            lastScroll = glm::vec3(0, 0, tickCount);
        return scroll;
    }


    //Default Callbacks
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
            if (!isPanelVisible())
            {
                for (auto &callback : customKeyCallBacks)
                {
                    callback(window, key, action);
                }
            }
                //Call panel key callbacks
            else
                for (auto &panel : currentPanels)
                    if (panel->getVisibility() && panel->keyCallback != nullptr)
                        panel->keyCallback(key, action);
        }

        void mouseButtonCallback(GLFWwindow *window, int button, int action, int mode)
        {
            mouse[button] = action;
            if (!isPanelVisible() && !CGE::GUI::GUIManager::isMouseInGUI())
                for (auto &callback : customMouseButtonCallBacks)
                    callback(window, button, action);
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

    void setYourOwnKeyCallBack(const std::function<void(GLFWwindow *, int, int)> &keyCallback)
    {
        customKeyCallBacks.push_back(keyCallback);
    }

    void resetKeyCallBacks()
    {
        customKeyCallBacks.clear();
    }

    void addCustomMouseButtonCallBack(const std::function<void(GLFWwindow *, int, int)> &mouseButtonCallback)
    {
        customMouseButtonCallBacks.push_back(mouseButtonCallback);
    }

    void resetMouseButtonCallBacks()
    {
        customMouseButtonCallBacks.clear();
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
        if (isMouseGrabed)
            ungrabMouse();
        else
            grabMouse();
    }
}
