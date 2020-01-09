#pragma once

#include <memory>
#include "Loader.h"
#include <Loader/Models/TexturedModel.h>
#include <Loader/Models/TwoDAnimatedModel.h>
#include "Texture.h"

namespace CGE::Loader::resManager
{
    //Initialize the resource manager
    void init();

    void terminate();

    //Check if model and texture got already loaded and returns them
    SharedTexModel getTexModel(unsigned int ID);

    //Check if model got already loaded and returns it
    SharedMesh getModel(unsigned int ID);

    //Check if texture got already loaded and returns it (it is an array of 1 texture)
    SharedTexture getTexture(unsigned int ID);

    //Scrap useless resources WARNING: MUST BE IN RENDER THREAD
    void scrap();
}