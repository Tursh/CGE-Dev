//
// Created by tursh on 1/24/19.
//

#pragma once

#include <Utils/Log.h>

namespace CGE::Animations
{
#define ANIMATION_PATH "res/graphics/animations/"

    struct Animation
    {

        virtual void tick()
        {
            logInfo("FONCTIONNE PAS!");
        };

    };

}