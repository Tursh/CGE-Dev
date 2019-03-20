#include <IO/Display.h>
#include "GUI/GUIComponent.h"

namespace CGE
{
	namespace GUI
	{

		GUIComponent::GUIComponent(const glm::vec2 &position, const glm::vec2 &dimension, Loader::TexturedModel *texModel)
				: position_(position), dimension_(dimension), texModel_(texModel)
		{
			glm::vec4 projection = glm::vec4(1.1f) * CGE::IO::getDisplay()->projectionMatrix;

			position_ /= (glm::vec2)projection;
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
	}
}
