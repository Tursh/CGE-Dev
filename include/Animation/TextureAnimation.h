//
// Created by tursh on 1/24/19.
//

#pragma once

#include <utility>
#include <vector>
#include "Animation.h"

namespace CGE::Animations
{

    class TextureAnimation : public Animation
    {
        /*
         * Array of the start and finish animation offset.
         * For example, animation 1 would start at texture 2 and end at texture 8
         * would give textureOffSets[1] first would be 2 and second would be 8
         * textureOffSets[0] is idle animation
         */
        std::vector<std::pair<unsigned int, unsigned int>> textureOffSets;

        //The duration of the on frame of the animation in ticks
        std::vector<unsigned int> frameDuration;

        unsigned int currentTexture, frameCountDown;
    public:
        unsigned int currentAnimation, idleAnimation;

        //The .anim that contains the texture offsets
        explicit TextureAnimation(const char *filePath);

        unsigned int getTextureToRender();

        //Stop current animation and start idle animation
        void returnToIdle();

        void tick() override;

    };

}
