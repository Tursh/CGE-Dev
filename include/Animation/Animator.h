//
// Created by tursh on 1/24/19.
//

#pragma once

#include "Animation.h"


namespace CGE::Animations::Animator
{

    //Add animation for management
    void addAnimation(Animation *animation);

    //Update all the known animations
    void updateAnimations();
}