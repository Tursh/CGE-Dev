#pragma once

#include <string>

#include "glm/ext/vector_float3.hpp"

namespace CGE
{
	namespace Text
	{
		namespace textRenderer
		{
			/*
			 * Initialize the renderer with the choosed font
			 */
			void init(const char* fontToUse);
			void clean();
			/*
			 * Render text to the screen
			 * text: text to render
			 * x and y : coordinates on the screen (-1 to 1)
			 * scale: text size
			 * color: color of the text
			 */
			void renderText(std::string text, float x, float y, float scale, glm::vec3 color,
					bool centered = true);
			/*
			 * Get the string length in pixels
			 */
			unsigned int getStringLength(std::string string, float size);
		}
	}
}
