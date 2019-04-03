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

        enum Mode
        {
            RELEASED = 0, OVER = 1, PRESSED = 2
        };

		class Button: public GUIComponent
		{
            Mode mode_;
			unsigned int type_;
			std::string text_;
			glm::vec2 textPosition_;
			float textSize_;
			bool pressing_ = false;
			//set the text size and position dynamicly so it is inside the button
			void setTextPosAndSize();

			std::function<void(void)> press;

		public:
			Button(unsigned int type, glm::vec2 position, glm::vec2 dimension,
					std::string text, std::function<void(void)> funcWhenPressed, char relativeToParent = 3);
			~Button();

			void render(GUIShader *shader) override;
			//Check if the mouse is not over or pressing it
			void checkEvent();

			//Getters and Setters
			std::string getText() const;
			void setText(std::string text);
			unsigned int getType() const;
			void setType(unsigned int type);
			void setPosition(const glm::vec2 & position) override;
			void setDimension(const glm::vec2 & dimension) override;
		};

	}
}
