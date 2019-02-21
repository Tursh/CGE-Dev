#pragma once
#include "GUIShader.h"

namespace CGE
{
	namespace GUI
	{
		namespace GUIRenderer
		{

			void init();
			GUIShader* getGUIShader();
			void loadProjectionMatrix(glm::mat4 matrix);

		}
	}
}
