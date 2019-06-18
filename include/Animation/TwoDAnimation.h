//
// Created by tursh on 1/24/19.
//

#pragma once

#include <utility>
#include <vector>
#include "Animation.h"

namespace CGE::Animations
{

    class TwoDAnimation : public Animation
    {
        /**
         * Array of the start and finish animation offset.
         * For example, an animation that start at frame 2 and finish at frame 8
         * Animation at index 0 is the idle animation
         */
        std::vector<std::pair<unsigned int, unsigned int>> textureOffSets_;

        /**
         * The duration of the on frame of the animation in ticks
         */
        std::vector<unsigned int> frameDuration_;

        unsigned int currentTexture = 0, frameCountDown_ = 0;
    protected:
        unsigned int currentAnimation_ = 0, idleAnimation_ = 0;
    public:

        //The file.anim that contains the texture offsets
        explicit TwoDAnimation(const char *filePath);

        //Return the texture for the current animation
        unsigned int getTextureToRender();

        //Stop current animation and start idle animation
        void returnToIdle();

        //Update the animation
        void tick() override;

        void setCurrentAnimation(unsigned int currentAnimation);

        unsigned int getCurrentAnimation() const;

        unsigned int getIdleAnimation() const;

        void setIdleAnimation(unsigned int idleAnimation);

    };

}
