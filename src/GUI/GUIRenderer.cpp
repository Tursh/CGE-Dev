#include "GUI/GUIRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GUI/GUIRenderer.h>
#include <GUI/GUIComponent.h>

#include "IO/Display.h"

namespace CGE
{
	namespace GUI
	{

		namespace GUIRenderer
		{

			GUIShader* shader;

			void init()
			{
				shader = new GUIShader;
			}

			GUIShader* getGUIShader()
			{
				return shader;
			}

            void resetDisplayResolution(const glm::vec2 &newResolution)
			{

			}

            void render(GUIComponent *component)
            {
                shader->start();
                const glm::vec2 &position = component->getPosition();
                const glm::vec2 &dimension = component->getDimension();
                //Load the transformation matrix
                glm::mat4 transMatrix(1);
                transMatrix = glm::translate(transMatrix, glm::vec3( // @suppress("Invalid arguments")
                        position.x, position.y, 0.0f));
                transMatrix = glm::scale(transMatrix, glm::vec3( // @suppress("Invalid arguments")
                        dimension.x, dimension.y, 1.0f));
                shader->setTransformationMatrix(transMatrix);
                //Render the component with their custom draw function
                component->draw();
                shader->stop();
            }

        }

	}
}
