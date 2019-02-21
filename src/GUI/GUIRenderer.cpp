#include "GUI/GUIRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GUI/GUIRenderer.h>

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

            void loadProjectionMatrix(glm::mat4 matrix)
            {
                shader->start();
                shader->setProjectionMatrix(matrix);
                shader->stop();
            }

        }

	}
}
