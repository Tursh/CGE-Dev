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
                : GUIComponent(position, dimension),
                  type_(type), parent_(nullptr),
                  rawPosition_(position), rawDimension_(dimension),
                  text_(std::move(text)), textPosition_(glm::vec2()), textSize_(1),
                  press(funcWhenPressed),
                  texModel_(Loader::resManagement::getFlat2DAnimation(type_))
        {
            setTextPosAndSize();
        }

        Button::~Button()
        {
            delete texModel_;
        }

        void Button::draw()
        {
            if (visible_)
            {
                //Get the shader
                GUIShader *shader = GUIRenderer::getGUIShader();
                shader->start();
                //Load the transformation matrix
                glm::mat4 transMatrix(1);
                transMatrix = glm::translate(transMatrix, glm::vec3( // @suppress("Invalid arguments")
                        position_.x, position_.y, -0.9f));
                transMatrix = glm::scale(transMatrix, glm::vec3( // @suppress("Invalid arguments")
                        dimension_.x, dimension_.y, 1));
                shader->setTransformationMatrix(transMatrix);
                //Render the button
                texModel_->render(mode_);
                shader->stop();
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
                //Apply the modification made by the projection matrix
                const glm::mat4 &projectionMatrix = GUIRenderer::getGUIShader()->getProjectionMatrix();
                glm::vec2 position = (glm::vec4(position_.x, position_.y, 0, 0) / 0.9f) * projectionMatrix;
                glm::vec2 dimension = (glm::vec4(dimension_.x, dimension_.y, 0, 0) / 0.9f) * projectionMatrix;
                //Check if the mouse is on the button
                if (position.x - dimension.x <= mousePos.x
                    && mousePos.x <= position.x + dimension.x
                    && position.y - dimension.y <= mousePos.y
                    && mousePos.y <= position.y + dimension.y)
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

        const static float MIN_TEXT_SIZE = 0.2f;

        void Button::setTextPosAndSize()
        {
            IO::Display *display = IO::getDisplay();
            glm::vec2 dimension = (glm::vec4(dimension_.x, dimension_.y, 0, 0) / 0.9f)
                                  * GUIRenderer::getGUIShader()->getProjectionMatrix();
            for (textSize_ = MIN_TEXT_SIZE;
                 dimension.x * 0.5f >
                 static_cast<float>(Text::textRenderer::getStringLength(text_, textSize_)) / display->width
                 && dimension.y * 0.6f > textSize_ * 40 / display->height; textSize_ += 0.01f);
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
            //Don't ask me what is this I don't even understand myself
            glm::vec2 projection = glm::vec4(1.1f) * CGE::IO::getDisplay()->projectionMatrix;

            rawPosition_ = position;
            if (parent_ != nullptr)
                position_ = (parent_->getPosition() + parent_->getDimension() * position / projection);
            else
                position_ = position;

            position_.y *= 1.75f;

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

    }
}
