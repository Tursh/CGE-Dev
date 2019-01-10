#pragma once
#include <glm/vec2.hpp>

namespace CGE
{
	namespace GUI
	{

		class GUIComponent
		{
		protected:
			glm::vec2 position_;
			glm::vec2 dimension_;
			bool visible_ = true;
		public:
			GUIComponent(const glm::vec2 &position, const glm::vec2 &dimension);

			//Getters setters
			const glm::vec2 &getPosition() const;

			void setPosition(const glm::vec2 &position);

			const glm::vec2 &getDimension() const;

			void setDimension(const glm::vec2 &dimension);

			const bool &getVisibility() const;

			void setVisibility(const bool &visibility);
		};

	}
}
