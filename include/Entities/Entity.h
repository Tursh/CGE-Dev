//
// Created by tursh on 1/17/19.
//

#pragma once


#include <glm/vec3.hpp>
#include <Loader/Texture.h>

namespace CGE
{
    namespace Entities
    {
        struct Entity
        {
            unsigned int ID;
            glm::vec3 position_;
            glm::vec3 rotation_;

            void render();
        };
    }
}
