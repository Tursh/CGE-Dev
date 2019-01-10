#pragma once
#include "Loader.h"

namespace CGE
{
	namespace Loader
	{

		/*Texture Manager*/
		class Texture
		{
			unsigned int ID;
			unsigned int width, height, bpp;
		public:
			/*Constructor for the maps*/
			Texture();

			/*Texture constructor*/
			Texture(unsigned int &ID, unsigned int width, unsigned int height, unsigned int bpp);

			/*Bind current texture to render*/
			void bind();

			/*Change the wrapping*/
			void changeWrapping(unsigned int newWrap);

			/*Change the filtering*/
			void changeFiltering(unsigned int newFilter);

			/*Delete texture*/
			void destroy();
		};

		/*Load texture from file*/
		Texture *loadTexture(const char *filePath);

		/*Textured model to render*/
		class TexturedModel
		{
			/*Texture ID pointer*/
			Texture &TEX;
			/*Model*/
			Model &MODEL;
		public:
			TexturedModel(Model &model, Texture &texture);

			void render();

			void bind();

			const unsigned int &indicesCount();
		};

	}
}
