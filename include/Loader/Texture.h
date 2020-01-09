#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <memory>

namespace CGE::Loader
{

    /*Texture Manager*/
    class Texture
    {
        unsigned int ID;
        int width, height, bpp;
        glm::ivec2 atlasCount_;
    public:
        explicit Texture(glm::ivec2 atlasCount = glm::ivec2(1));

        ~Texture();

        /*
         * Bind current texture to render
         */
        void bind();

        /*
         * Change the wrapping
         */
        void changeWrapping(unsigned int newWrap);

        /*
         * Change the filtering
         */
        void changeFiltering(unsigned int newFilter);

        /*
         * Load texture from file
         */
        void loadTexture(const char *filePath);

        /*
         * Return the size of the texture in pixels
         */
        glm::vec2 getSize();

        /*
         * For texture atlas
         * return coordinates in this order:
         * {x-, y-, x+, y+}
         */
        glm::vec4 getTextureLimits(unsigned int atlasIndex = 0);
    };

    typedef std::shared_ptr<Texture> SharedTexture;
}
