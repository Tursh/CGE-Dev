#pragma once

#include "Loader.h"
#include "Texture.h"

namespace CGE
{
	namespace Loader
	{
		namespace resManagement
		{
			void init();

			TexturedModel getTexModel(unsigned int ID);

			Model &getModel(unsigned int ID);

			Texture &getTexture(unsigned int ID);

			void clearBuffers();

		}
	}
}