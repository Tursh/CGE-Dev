#pragma once

#include <memory>
#include "Loader.h"
#include <Loader/Meshes/TexturedMesh.h>
#include "Texture.h"

namespace CGE::Loader::resManager
{
    /**
     * Initialize the resource manager
     */
    void init();

    /**
     * Free all resources
     */
    void terminate();

    /**
     * Check if mesh and texture got already loaded and returns them
     * @param ID TexMesh ID (In graphics.index -> R <ID> <MeshID> <TexID>)
     * @return The textured model
     */
    SharedTexMesh getTexMesh(unsigned int ID);

    /**
     * Check if model got already loaded and returns it
     * @param ID Mesh ID (In graphics.index -> M <MeshID> <Path from res/graphics/meshes/>)
     * @return The mesh
     */
    SharedMesh getMesh(unsigned int ID);

    /**
     * Check if texture got already loaded and returns it
     * @param ID Texture ID (In graphics.index -> T <TexID> <Path from res/graphics/textures/> <Atlas size x> <Atlas size y>)
     * @return The texture
     */
    SharedTexture getTexture(unsigned int ID);

    //Scrap useless resources WARNING: MUST BE IN RENDER THREAD
    void scrap();
}