//
// Created by tursh on 1/17/19.
//

#pragma once

#include <vector>

#include <Shader/ShaderProgram.h>
#include <World/World.h>

namespace CGE
{
    namespace Renderer
    {
        namespace WorldRenderer
        {
            void init();
            //Call when the display is resized
            void genNewProjectionMatrix();

            void render(const World::World &world);
        };

    }
}

