#include <GL/glew.h>	//GL*
#include <Loader/Model.h>
#include <extern/stb_image.h>    //decodePNG
#include <Loader/Texture.h>    //Texture
#include <Utils/Log.h>        //logError
#include <Utils/GLDebug.h>
#include <iostream>
#include <string>
#include <vector>		//std::vector

namespace CGE
{
	namespace Loader
	{

		Texture *loadTexture(const char *filePath)
		{
			int width, height, bpp;

			stbi_set_flip_vertically_on_load(true);
			unsigned char* buffer = stbi_load(filePath, &width, &height, &bpp, 4);

			if (buffer == 0)
				logError("Failed to load " << filePath);

			unsigned int texture;
			GLCall(glGenTextures(1, &texture));
			GLCall(glBindTexture(GL_TEXTURE_2D, texture));
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));

			return new Texture(texture, width, height, bpp);
		}

		Texture::Texture() {}

		Texture::Texture(unsigned int &ID, unsigned int width, unsigned int height, unsigned int bpp)
				: ID(ID), width(width), height(height), bpp(bpp) {}

		void Texture::destroy()
		{
			GLCall(glDeleteTextures(1, &ID));
		}

		void Texture::bind()
		{
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
		}

		void Texture::changeWrapping(GLenum param)
		{
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param));
		}

		void Texture::changeFiltering(GLenum param)
		{
			GLCall(glBindTexture(GL_TEXTURE_2D, ID));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param));
		}

		TexturedModel::TexturedModel(Model &model, Texture &texture)
				: TEX(texture), MODEL(model) {}

		void TexturedModel::render()
		{
			TEX.bind();
			MODEL.render(true);
		}

		void TexturedModel::bind()
		{
			TEX.bind();
			MODEL.bind();
		}

		const unsigned int &TexturedModel::indicesCount()
		{
			return MODEL.vertexCount;
		}

	}
}
