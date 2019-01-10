#include "GUI/Panel.h"

namespace CGE
{
	namespace GUI
	{

		Panel::Panel(const glm::vec2 position, const glm::vec2 dimension)
				: GUIComponent(position, dimension)
		{
		}

		Panel::~Panel()
		{
			for (auto button : buttons_)
				delete button;
		}

		void Panel::addButton(Button* newButton)
		{
			newButton->setParent(this);
			buttons_.push_back(newButton);
		}

		void Panel::draw()
		{
			for (auto button : buttons_)
				button->draw();
		}

		void Panel::checkEvents()
		{
			for (auto button : buttons_)
			{
				button->checkEvent();
			}
		}
	}
}
