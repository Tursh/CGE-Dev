#pragma once
#include <GUI/GUIShader.h>
#include <GUI/GUIComponent.h>

namespace CGE
{
	namespace GUI
	{
		namespace GUIRenderer
		{

			void init();
			void render(GUIComponent *component);
			void resetDisplayResolution(const glm::vec2 &newResolution);

		}
	}
}
