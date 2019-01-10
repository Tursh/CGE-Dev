#pragma once
#include <vector>

#include "GUIComponent.h"
#include "Button.h"

namespace CGE
{
	namespace GUI
		{
			class Button;

			class Panel : public GUIComponent
			{
				std::vector<Button*> buttons_;

			public:

				Panel(glm::vec2 position, glm::vec2 dimension);

				~Panel();

				void addButton(Button* newButton);

				void draw();

				void checkEvents();
			};
		}
}
