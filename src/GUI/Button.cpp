#include <utility>

#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <GUI/Button.h>
#include <GUI/GUIRenderer.h>
#include <IO/Display.h>
#include <IO/Input.h>
#include <Loader/RessourceManager.h>
#include <Text/TextRenderer.h>
#include <algorithm>

namespace CGE
{
    namespace GUI
    {

        Button::Button(const ButtonType type, const glm::vec2 position, const glm::vec2 dimension,
                       std::string text, std::function<void(void)> funcWhenPressed)
                : GUIComponent(position, dimension, Loader::resManagement::getFlat2DAnimation(type)),
                  type_(type), parent_(nullptr),
                  rawPosition_(position), rawDimension_(dimension),
                  text_(std::move(text)), textPosition_(glm::vec2()), textSize_(1),
                  press(std::move(funcWhenPressed))
        {
            setTextPosAndSize();


            std::function<void(void)> test = std::bind(&Button::draw, this);
        }

        Button::~Button()
        {
            delete texModel_;
        }

        void Button::render()
        {
            if (visible_)
            {
                //Get the shader
                GUIRenderer::render(this);
                //dimension_.x -= 0.001f;
                //setDimension(dimension_);
                //Render text
                CGE::Text::textRenderer::renderText(text_, textPosition_.x, textPosition_.y,
                                                    textSize_,
                                                    {1, 1, 1});
            }
        }

        void Button::checkEvent()
        {
            if (visible_)
            {
                glm::vec2 mousePos = IO::input::getCursorPos();
                IO::Display *display = IO::getDisplay();
                //Change pixel position to opengl coordinate
                mousePos.x = mousePos.x / display->width * 2 - 1;
                mousePos.y = (display->height - mousePos.y) / display->height * 2 - 1;
                //Check if the mouse is on the button
                if (position_.x - dimension_.x <= mousePos.x
                    && mousePos.x <= position_.x + dimension_.x
                    && position_.y - dimension_.y <= mousePos.y
                    && mousePos.y <= position_.y + dimension_.y)
                {
                    if (IO::input::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
                    {
                        mode_ = PRESSED;
                        pressing_ = true;
                    } else
                    {
                        mode_ = OVER;
                        if (pressing_)
                        {
                            press();
                            pressing_ = false;
                        }
                    }
                } else
                {
                    pressing_ = false;
                    mode_ = RELEASED;
                }
            }

        }

        const static float MIN_TEXT_SIZE = 0.01f;

        void Button::setTextPosAndSize()
        {
            CGE::IO::Display *display = CGE::IO::getDisplay();
            for (textSize_ = MIN_TEXT_SIZE;
                 dimension_.x * 0.4f >
                 static_cast<float>(Text::textRenderer::getStringLength(text_, textSize_))
                 && dimension_.y * 0.5f > textSize_ * 120 / display->height; textSize_ += 0.001f);
            textPosition_ = position_;
            textPosition_.y -= textSize_ / 10;
        }

        //Getters and Setters
        ButtonType Button::getType() const
        {
            return type_;
        }

        void Button::setType(ButtonType type)
        {
            type_ = type;
        }

        void Button::setPosition(glm::vec2 position)
        {
            rawPosition_ = position;
            if (parent_ != nullptr)
                position_ = (parent_->getPosition() + parent_->getDimension() * position);
            else
                position_ = position;

            setTextPosAndSize();
        }

        void Button::setDimension(glm::vec2 dimension)
        {
            rawDimension_ = dimension;
            if (parent_ != nullptr && type_ != SLOT)
                dimension_ = parent_->getDimension() * dimension;
            else
                dimension_ = dimension;
            setTextPosAndSize();
        }

        Panel *Button::getParent() const
        {
            return parent_;
        }

        void Button::setParent(Panel *parent)
        {
            parent_ = parent;
            setPosition(rawPosition_);
            setDimension(rawDimension_);
        }

        std::string Button::getText() const
        {
            return text_;
        }

        void Button::setText(std::string text)
        {
            this->text_ = text;
            setTextPosAndSize();
        }

        void Button::draw()
        {
            ((CGE::Loader::TwoDAnimatedModel *)texModel_)->render(mode_);
        }
    }
}
