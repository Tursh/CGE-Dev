#include "GUI/GUIRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GUI/GUIRenderer.h>
#include <GUI/GUIComponent.h>
#include <GUI/Button.h>

#include "IO/Display.h"

namespace CGE
{
    namespace GUI
    {

        namespace GUIRenderer
        {

            glm::vec2 displayScale = glm::vec2(1);

            GUIShader *shader;

            void init()
            {
                shader = new GUIShader;
            }

            GUIShader *getGUIShader()
            {
                return shader;
            }

            void resetDisplayResolution(const glm::vec2 &newResolution)
            {
                displayScale = glm::vec2(newResolution.x / CGE::IO::DEFAULT_WIDTH,
                                         newResolution.y / CGE::IO::DEFAULT_HEIGHT);
            }

            void render(GUIComponent *component)
            {
                shader->start();

                glm::vec2 position = component->getPosition();
                glm::vec2 dimension = component->getDimension() / displayScale;

                const char &scalePosition = component->getScalePosition();
                if(scalePosition & 1)
                    position.x /= displayScale.x;
                if((scalePosition >> 1) & 1)
                    position.y /= displayScale.y;
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

            const glm::vec2 &getDisplayScale()
            {
                return displayScale;
            }

        }

    }
}
