#pragma once
#include <glm/vec2.hpp>
#include <Loader/Models/TexturedModel.h>

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
			Loader::TexturedModel *texModel_;
		public:
			GUIComponent(const glm::vec2 &position, const glm::vec2 &dimension, Loader::TexturedModel *texModel);

			virtual void draw() = 0;

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
