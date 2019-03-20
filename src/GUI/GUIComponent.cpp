#include <IO/Display.h>
#include "GUI/GUIComponent.h"

namespace CGE
{
    namespace GUI
    {

        GUIComponent::GUIComponent(ComponentType type, char scalePosition, const glm::vec2 &position,
                                   const glm::vec2 &dimension, Loader::TexturedModel *texModel)
                : type_(type), scalePosition_(scalePosition), position_(position), dimension_(dimension),
                  texModel_(texModel)
        {
        }

        const glm::vec2 &GUIComponent::getPosition() const
        {
            return position_;
        }

        void GUIComponent::setPosition(const glm::vec2 &position)
        {
            this->position_ = position;
        }

        const glm::vec2 &GUIComponent::getDimension() const
        {
            return dimension_;
        }

        void GUIComponent::setDimension(const glm::vec2 &dimension)
        {
            this->dimension_ = dimension;
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

        const char &GUIComponent::getScalePosition() const
        {
            return scalePosition_;
        }
    }
}
