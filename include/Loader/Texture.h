#pragma once

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <memory>

namespace CGE::Loader
{

    /*Texture Manager*/
    class Texture
    {
        unsigned int ID_ = 0;
        int width_ = 0, height_ = 0, bpp_ = 0;
        glm::ivec2 atlasCount_;
    public:
        explicit Texture(glm::ivec2 atlasCount = glm::ivec2(1));

        ~Texture();

        /**
         * Bind current texture to render
         */
        void bind();

        /**
         * Change the wrapping
         * @param newWrap New wrap (GL_REPEAT, GL_CLAMP_TO_EDGE or GL_CLAMP_TO_BORDER)
         */
        void changeWrapping(GLenum newWrap);

        /**
         * Change the filtering
         * @param newFilter New Filter (GL_NEAREST or GL_LINEAR)
         */
        void changeFiltering(GLenum newFilter);

        /**
         * Set texture parameters for more info: <http://docs.gl/gl3/glTexParameter>
         */
        void changeTexParameter(GLenum target, GLenum pname, GLint param);
        /**
         * Set texture parameters for more info: <http://docs.gl/gl3/glTexParameter>
         */
        void changeTexParameter(GLenum target, GLenum pname, GLfloat param);

        /**
         * Load texture from file
         * @param filePath Path to file from "res/graphics/texture"
         */
        void loadTexture(const char *filePath);

        /**
         * @return The size of the texture in pixels
         */
        glm::vec2 getSize();

        /**
         * To get texture atlas texture limit
         * @param atlasIndex atlas index counting from left to right and top to bottom
         * @return Coordinates in this order: {x-, y-, x+, y+}
         */
        glm::vec4 getTextureLimits(unsigned int atlasIndex = 0);
    };

    typedef std::shared_ptr<Texture> SharedTexture;
}
