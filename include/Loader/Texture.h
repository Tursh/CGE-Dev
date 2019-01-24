#pragma once

namespace CGE
{
	namespace Loader
	{

		/*Texture Manager*/
		class Texture
		{
			unsigned int ID;
			int width, height, bpp;
		public:
			Texture();

			~Texture();

			/*Bind current texture to render*/
			void bind();

			/*Change the wrapping*/
			void changeWrapping(unsigned int newWrap);

			/*Change the filtering*/
			void changeFiltering(unsigned int newFilter);

			void loadTexture(const char *filePath);
		};

		/*Load texture from file*/
		Texture *loadTextures(const char **filePaths, unsigned count);

	}
}
