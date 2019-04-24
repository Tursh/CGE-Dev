#include <IO/Display.h>
#include <GUI/GUIComponent.h>
#include <GUI/GUIManager.h>
#include <glm/ext/matrix_transform.hpp>
#include <IO/Input.h>

namespace CGE::GUI
{

    GUIComponent::GUIComponent(ComponentType type, const glm::vec2 &position,
                               const glm::vec2 &dimension, std::shared_ptr<Loader::TexturedModel> texModel,
                               char relativeToParent)
            : type_(type), parent_(nullptr), texModel_(texModel), rawPosition_(position),
              rawDimension_(dimension), relativeToParent_(relativeToParent)
    {
        setPosition(position);
        setDimension(dimension);
        GUIManager::addComponent(this);
    }

    const glm::vec2 &GUIComponent::getPosition() const
    {
        return position_;
    }

    void GUIComponent::setPosition(const glm::vec2 &position)
    {
        rawPosition_ = position;
        if (parent_ != nullptr && relativeToParent_ & 1)
            position_ = (parent_->getPosition() + parent_->getDimension() * position);
        else
            position_ = position;
    }

    const glm::vec2 &GUIComponent::getDimension() const
    {
        return dimension_;
    }

    void GUIComponent::setDimension(const glm::vec2 &dimension)
    {
        rawDimension_ = dimension;
        if (parent_ != nullptr && relativeToParent_ & 2)
            dimension_ = parent_->getDimension() * dimension;
        else
            dimension_ = dimension / GUIManager::getDisplayScale();
    }

    const bool &GUIComponent::getVisibility() const
    {
        return this->visible_;
    }

    void GUIComponent::setVisibility(const bool &visibility)
    {
        this->visible_ = visibility;
    }

    const ComponentType &GUIComponent::getType_() const
    {
        return type_;
    }

    void GUIComponent::resetDisplayScale()
    {
        setPosition(rawPosition_);
        setDimension(rawDimension_);
    }

    void GUIComponent::render(GUIShader *shader)
    {
        if (!visible_)
            return;
        shader->start();
        prepareRender(shader);
        texModel_->render();
        shader->stop();
    }

    void GUIComponent::prepareRender(GUIShader *shader)
    {
        //Load the transformation matrix
        glm::mat4 transMatrix(1);
        transMatrix = glm::translate(transMatrix, glm::vec3( // @suppress("Invalid arguments")
                position_.x, position_.y, 0.0f));
        transMatrix = glm::scale(transMatrix, glm::vec3( // @suppress("Invalid arguments")
                dimension_.x, dimension_.y, 1.0f));
        shader->setTransformationMatrix(transMatrix);
    }

    GUIComponent *GUIComponent::getParent() const
    {
        return parent_;
    }

    void GUIComponent::setParent(GUIComponent *parent)
    {
        parent_ = parent;
        setPosition(rawPosition_);
        setDimension(rawDimension_);
        GUIManager::removeComponent(this);
    }

    bool GUIComponent::isMouseInPanel()
    {
        //Get mouse position
        glm::vec2 mousePos = IO::input::getCursorPos();
        IO::Display *display = IO::getDisplay();
        //Change pixel position to openGL coordinate
        mousePos.x = mousePos.x / display->width * 2 - 1;
        mousePos.y = (display->height - mousePos.y) / display->height * 2 - 1;
        //Check if the mouse is on the button
        return position_.x - dimension_.x <= mousePos.x
            && mousePos.x <= position_.x + dimension_.x
            && position_.y - dimension_.y <= mousePos.y
            && mousePos.y <= position_.y + dimension_.y;
    }

    const glm::vec2 &GUIComponent::getRawPosition() const
    {
        return rawPosition_;
    }

    const glm::vec2 &GUIComponent::getRawDimension() const
    {
        return rawDimension_;
    }
}
