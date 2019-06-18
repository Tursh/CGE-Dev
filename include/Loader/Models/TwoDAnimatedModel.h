//
// Created by tursh on 1/24/19.
//

#pragma once

#include <Animation/TwoDAnimation.h>
#include "TexturedModel.h"

namespace CGE::Loader
{

    class TwoDAnimatedModel : public TexturedModel
    {
        float sizeScale_;
        Animations::TwoDAnimation *animation_;
    public:

        TwoDAnimatedModel(TexturedModel texturedModel, float size, Animations::TwoDAnimation *animation);

        ~TwoDAnimatedModel();

        glm::vec2 getTextureSize() override ;

        void setIdleAnimation(unsigned int ID);

        void startAnimation(unsigned int ID);

        void stopAnimation();

        unsigned int getCurrentAnimation();

        void render(unsigned int offset);

        void render() override;
    };

}