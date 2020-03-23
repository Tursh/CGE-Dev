//
// Created by tursh on 1/24/19.
//

#pragma once

namespace CGE::Animations
{
#define ANIMATION_PATH "res/graphics/animations/"

    struct Animation
    {

        virtual void tick() = 0;

    };

}