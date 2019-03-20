#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <Loader/Models/TexturedModel.h>
#include <Loader/Models/TwoDAnimatedModel.h>
#include <functional>
#include <ostream>

#include "GUIComponent.h"
#include "Panel.h"

namespace CGE
{
	namespace GUI
	{

		class Panel;

		enum ButtonType
		{
            BUTTON_DEFAULT = 10000, SLOT = 10001
        };

        enum Mode
        {
            RELEASED = 0, OVER = 1, PRESSED = 2
        };

		class Button: public GUIComponent
		{
            Mode mode_;
			ButtonType type_;
			Panel* parent_;
			glm::vec2 rawPosition_;
			glm::vec2 rawDimension_;
			std::string text_;
			glm::vec2 textPosition_;
			float textSize_;
			bool pressing_ = false;
			//set the text size and position dynamicly so it is inside the button
			void setTextPosAndSize();

			std::function<void(void)> press;

		public:
			Button(ButtonType type, glm::vec2 position, glm::vec2 dimension,
					std::string text, std::function<void(void)> funcWhenPressed);
			~Button();

			void render();
			//Check if the mouse is not over or pressing it
			void checkEvent();

			virtual void draw() override;

			//Getters and Setters
			std::string getText() const;
			void setText(std::string text);
			ButtonType getType() const;
			void setType(ButtonType type);
			void setPosition(glm::vec2 position);
			void setDimension(glm::vec2 dimension);
			void setParent(Panel* parent);
			Panel* getParent() const;
		};

	}
}
