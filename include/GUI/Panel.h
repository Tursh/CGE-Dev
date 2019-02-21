#pragma once
#include <vector>

#include "GUIComponent.h"
#include "Button.h"

namespace CGE
{
	namespace GUI
		{
			enum PanelType
			{
				PANEL_INVISIBLE, PANEL_DEFAULT = 20000
			};

			class Button;

			class Panel : public GUIComponent
			{
				PanelType type_;
				Loader::TexturedModel *texModel_;
			protected:
				std::vector<Button*> buttons_;

			public:

				Panel(glm::vec2 position, glm::vec2 dimension, PanelType type);

				~Panel();

				void addButton(Button *newButton);

				void draw();

				void checkEvents();
			};
		}
}
