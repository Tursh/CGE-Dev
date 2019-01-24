#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <Loader/Models/TexturedModel.h>

#include "GUIComponent.h"
#include "Panel.h"

namespace CGE
{
	namespace GUI
	{

		class Panel;

		enum ButtonType
		{
            DEFAULT = 10000
        };

        enum Mode
        {
            RELEASED = 0, OVER = 1, PRESSED = 2
        };

		class Button: public GUIComponent
		{
            Mode mode_;
			ButtonType type_;
            Loader::TexturedModel texModel_;
			Panel* parent_;
			glm::vec2 rawPosition_;
			glm::vec2 rawDimension_;
			std::string text_;
			glm::vec2 textPosition_;
			float textSize_;
			bool pressing_ = false;

			void (*press)();

			//set the text size and position dynamicly so it is inside the button
			void setTextPosAndSize();

		public:
			Button(const ButtonType type, const glm::vec2 position, const glm::vec2 dimension,
					std::string text, void (*funcWhenPressed)());

			void draw();
			//Check if the mouse is not over or pressing it
			void checkEvent();

			//Getters and Setters
			std::string getText() const;
			void setText(std::string text);
			ButtonType getType() const;
			void setType(ButtonType type);
			void setPosition(glm::vec2 position);
			void setDimension(glm::vec2 dimension);
			Panel* getParent() const;
			void setParent(Panel* parent);
		};

	}
}
