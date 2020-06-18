#include <utility>

#include <Loader/RessourceManager.h>
#include <GUI/Button.h>
#include <IO/Window.h>
#include <IO/Input.h>
#include <GUI/Text/TextRenderer.h>
#include <GUI/GUIManager.h>
#include <GLFW/glfw3.h>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace CGE::GUI
{

    Button::Button(const unsigned int type, const glm::vec2 position, const glm::vec2 dimension,
                   std::string text, std::function<void(void)> funcWhenPressed, char relativeToParent)
            : GUIComponent(BUTTON, position, dimension,
                           Loader::resManager::getTexMesh(type), relativeToParent),
              type_(type), mode_(RELEASED),
              text_(std::move(text)), textPosition_(glm::vec2()), textSize_(1),
              press(std::move(funcWhenPressed))
    {
        setPosition(position);
        setDimension(dimension);
        setTextPosAndSize();
        //GUIManager::addComponent(this);
    }

    Button::~Button()
    {
        GUIManager::removeComponent(this);
    }

    void Button::render(GUIShader *shader)
    {
        if (!visible_)
            return;
        //Get button
        shader->start();
        prepareRender(shader);
        ((Loader::TwoDAnimatedMesh *) texMesh_.get())->render(mode_);
        shader->stop();
        //Render text
        CGE::GUI::Text::TextRenderer::renderText(text_, textPosition_,
                                                 textSize_,
                                                 {1, 1, 1});
    }

    void Button::checkEvent()
    {
        if (visible_)
        {
            //Check if the mouse is on the button
            if (isMouseInPanel())
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

    const static float MIN_TEXT_SIZE = 0.001f;

    void Button::setTextPosAndSize()
    {
        CGE::IO::Window *display = CGE::IO::getWindow();
        for (textSize_ = MIN_TEXT_SIZE;
             dimension_.x * 0.75f >
             static_cast<float>(Text::TextRenderer::getStringLength(text_, textSize_))
             && dimension_.y * 0.85f > textSize_ * 120 / display->getHeight(); textSize_ += 0.001f);
        textPosition_ = position_;
        textPosition_.y -= textSize_ / 20;
    }

    //Getters and Setters
    unsigned int Button::getType() const
    {
        return type_;
    }

    void Button::setType(unsigned int type)
    {
        type_ = type;
    }

    void Button::setPosition(const glm::vec2 &position)
    {
        GUIComponent::setPosition(position);
        setTextPosAndSize();
    }

    void Button::setDimension(const glm::vec2 &dimension)
    {
        GUIComponent::setDimension(dimension);
        setTextPosAndSize();
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
}
