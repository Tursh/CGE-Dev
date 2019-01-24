//
// Created by tursh on 1/24/19.
//

#pragma once

#include <utility>
#include <vector>
#include "Animation.h"

namespace CGE
{
    namespace Animations
    {

        class TextureAnimation : public Animation
        {
            unsigned int currentAnimations, currentTexture, frameCountDown;
            /*
             * Array of the start and finish animation offset.
             * For example, animation 1 would start at texture 2 and end at texture 8
             * would give textureOffSets[1] first would be 2 and second would be 8
             * textureOffSets[0] is idle animation
             */
            std::vector<std::pair<unsigned int, unsigned int>> textureOffSets;

            //The duration of the on frame of the animation in ticks
            std::vector<unsigned int> frameDuration;

        public:
            //The .anim that contains the texture offsets
            TextureAnimation(const char *filePath);

            void setCurrentAnimation(unsigned int ID);

            unsigned int getTextureToRender();

            void tick() override;

        };

    }
}
