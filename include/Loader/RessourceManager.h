#pragma once

#include <memory>
#include <Loader/Models/TexturedModel.h>
#include <Loader/Models/TwoDAnimatedModel.h>
#include "Loader.h"
#include "Texture.h"

namespace CGE::Loader::resManager
		{
            //Initialize the resource manager
            void init();

            //Check if model and texture got already loaded and returns them
            std::shared_ptr<TexturedModel> getTexModel(unsigned int ID);

            //Check if model got already loaded and returns it
            std::shared_ptr<Model> getModel(unsigned int ID);

            //Check if texture got already loaded and returns it (it is an array of 1 texture)
            std::shared_ptr<Texture[]> getTexture(unsigned int ID);

            //Check if the flat model and textures got already loaded and returns it
            std::shared_ptr<TwoDAnimatedModel> getFlat2DAnimation(unsigned int ID);

            //Check if textures got already loaded and returns it
            std::shared_ptr<Texture[]> get2DAnimationTextures(unsigned int ID);

            //Clear useless resources WARNING: MUST BE IN RENDER THREAD
            void clear();

		}