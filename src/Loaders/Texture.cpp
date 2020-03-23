#include <GL/glew.h>    //GL*
#include <Loader/Meshes/Mesh.h>
#include <extern/stb_image.h>    //decodePNG
#include <Loader/Texture.h>    //Texture
#include <Utils/Log.h>        //logError
#include <Utils/GLDebug.h>
#include <glm/vec2.hpp>

namespace CGE::Loader
{

    Texture::Texture(glm::ivec2 atlasCount)
            : ID_(0xffffffff), atlasCount_(atlasCount)
    {
    }

    void trashTexture(unsigned int texture);

    Texture::~Texture()
    {
        trashTexture(ID_);
    }

    void Texture::bind()
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, ID_));
    }

    void Texture::changeWrapping(GLenum param)
    {
        bind();
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param))
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param))
    }

    void Texture::changeFiltering(GLenum param)
    {
        bind();
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param))
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param))
    }

    void Texture::changeTexParameter(GLenum target, GLenum pname, GLint param)
    {
        bind();
        GLCall(glTexParameteri(target, pname, param))
    }

    void Texture::changeTexParameter(GLenum target, GLenum pname, GLfloat param)
    {
        bind();
        GLCall(glTexParameteri(target, pname, param))
    }

    void Texture::loadTexture(const char *fileName)
    {
        std::string filePath(R"(res/graphics/textures/)");
        filePath += fileName;

        stbi_set_flip_vertically_on_load(true);
        unsigned char *buffer = stbi_load(filePath.data(), &width_, &height_, &bpp_, 4);

        if (buffer == nullptr)
        logError("Failed to load " << filePath)

        GLCall(glGenTextures(1, &ID_))
        GLCall(glBindTexture(GL_TEXTURE_2D, ID_))
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer))
        //GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        //GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST))
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST))
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT))
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT))
        GLCall(glGenerateMipmap(GL_TEXTURE_2D))

        logInfo("Texture Loaded filePath: " << filePath << " ID: " << ID_);
    }

    glm::vec2 Texture::getSize()
    {
        return {width_ / atlasCount_.x, height_ / atlasCount_.y};
    }

    glm::vec4 Texture::getTextureLimits(unsigned int atlasIndex)
    {
        glm::vec4 texCoords;
        texCoords.x = (float)(atlasIndex % atlasCount_.x) / atlasCount_.x;
        texCoords.y = 1.0f - ((float)(atlasIndex / atlasCount_.x) / atlasCount_.y);
        texCoords.z = texCoords.x + 1.0f / atlasCount_.x;
        texCoords.w = texCoords.y - 1.0f / atlasCount_.y;

        return texCoords;
    }
}
