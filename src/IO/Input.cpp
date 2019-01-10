#include <glm/detail/type_vec2.hpp>
#include <IO/Display.h>
#include <Utils/Log.h>                        //logError
#include "IO/Input.h"
#include <iostream>

namespace CGE
{
	namespace IO
	{
		namespace input
		{

			static GLFWwindow* window;
			/*Keys and Button array*/
			static bool* keys;
			static bool* mouse;
			/*Last mouse position*/
			static glm::vec2 lastMousePos;

			void (*customKeyCallBack)(GLFWwindow* window, int key, int action);
			void (*customMouseButtonCallBack)(GLFWwindow* window, int button, int action);

			/*Initialize inputs*/
			void init()
			{
				window = getDisplay()->window;
				keys = new bool[348];
				mouse = new bool[10];
				for (int i = 0; i < 348; i++)
					keys[i] = false;
				for (int i = 0; i < 10; i++)
					mouse[i] = false;
				glfwSetKeyCallback(window, CallBacks::keyCallback);
				glfwSetMouseButtonCallback(window, CallBacks::mouseButtonCallback);
			}

			namespace CallBacks
			{
				/*Key callback function*/
				void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
				{
					if (key > 348)
					{
						logError(key << "is not listed as a key");
						return;
					}
					if (action != GLFW_REPEAT)
						keys[key] = action;
					if (customKeyCallBack != nullptr)
						customKeyCallBack(window, key, action);
				}

				/*Mouse callback fonction*/
				void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
				{
					mouse[button] = action;
					if (customMouseButtonCallBack != nullptr)
						customMouseButtonCallBack(window, button, action);
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

			void setYourOwnKeyCallBack(void (*keyCallBack)(GLFWwindow* window, int key, int action))
			{
				customKeyCallBack = keyCallBack;
			}

			void resetKeyCallBack()
			{
				customMouseButtonCallBack = nullptr;
			}

			void setYourOwnMouseButtonCallBack(
					void (*mouseButtonCallBack)(GLFWwindow* window, int button, int action))
			{
				customMouseButtonCallBack = mouseButtonCallBack;
			}

			void resetMouseButtonCallBack()
			{
				customMouseButtonCallBack = nullptr;
			}

			/*Return the movement of the mouse since the last call*/
			glm::vec2 getCursorShifting()
			{
				double x, y;
				glfwGetCursorPos(window, &x, &y);
				const glm::vec2 mousePos = glm::vec2((float) x, (float) y);
				glm::vec2 delta = mousePos - lastMousePos;
				lastMousePos = mousePos;
				return delta;
			}

			/*Get cursor position relative to the game window*/
			glm::vec2 getCursorPos()
			{
				double x, y;
				glfwGetCursorPos(window, &x, &y);
				return glm::vec2((float) x, (float) y);
			}
		}
	}
}
