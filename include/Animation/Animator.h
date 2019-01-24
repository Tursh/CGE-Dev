//
// Created by tursh on 1/24/19.
//

#pragma once

#include "Animation.h"

namespace CGE
{
    namespace Animations
    {
        //Get track of animations and update them every tick
        namespace Animator
        {

            void addAnimation(Animation *animation);

            void updateAnimations();

        }
    }
}