#pragma once
#include <glm/vec2.hpp>
#include <Loader/Models/TexturedModel.h>

namespace CGE
{
	namespace GUI
	{
		enum ComponentType
		{
			IMAGE, PANEL, BUTTON
		};

		class GUIComponent
		{
			ComponentType type_;
			//We use the 2 first bits as booleans
			char scalePosition_;
		protected:
			glm::vec2 position_;
			glm::vec2 dimension_;
			bool visible_ = true;
			Loader::TexturedModel *texModel_;
		public:
			GUIComponent(ComponentType type, char scalePosition, const glm::vec2 &position, const glm::vec2 &dimension, Loader::TexturedModel *texModel);

			virtual void draw() = 0;

			//Getters setters
			const ComponentType &getType_() const;

			const glm::vec2 &getPosition() const;

			void setPosition(const glm::vec2 &position);

			const glm::vec2 &getDimension() const;

			void setDimension(const glm::vec2 &dimension);

			const bool &getVisibility() const;

			void setVisibility(const bool &visibility);

			const char &getScalePosition() const;
		};

	}
}
