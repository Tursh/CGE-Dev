#pragma once

#include <string>

#include "glm/ext/vector_float3.hpp"
#include <glm/mat4x4.hpp>

namespace CGE ::GUI::Text::TextRenderer
{
    /**
     * Initialize the renderer with the chosen font
     */
    void init(const char *fontToUse);

    /**
     * Destroy all the resources used to render text
     */
    void terminate();


    void resetWindowDimension(const glm::vec2 &newResolution);

    /**
     *
     * @param text Text to render
     * @param position Coordinates on the screen ( (-1,-1) to  (1, 1) )
     * @param scale Font size
     * @param color Text color (RGB)
     * @param centered Centered at position or at the right bottom of the position
     */
    void renderText(std::string text, glm::vec2 position, float scale, const glm::vec3 &color,
                    bool centered = true);

    /**
     * Get the string length in pixels on screen
     */
    float getStringLength(std::string string, float size);

}
