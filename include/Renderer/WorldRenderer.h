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

            void render(const World::World &world);
        };

    }
}

