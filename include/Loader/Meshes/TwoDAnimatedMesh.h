//
// Created by tursh on 1/24/19.
//

#pragma once

#include <Animation/TwoDAnimation.h>
#include "TexturedMesh.h"

namespace CGE::Loader
{

    class TwoDAnimatedMesh : public TexturedMesh
    {
        float sizeScale_;
        Animations::TwoDAnimation *animation_;
    public:

        TwoDAnimatedMesh(TexturedMesh texturedMesh, float size, Animations::TwoDAnimation *animation);

        ~TwoDAnimatedMesh();

        glm::vec2 getTextureSize() override ;

        void setIdleAnimation(unsigned int ID);

        void startAnimation(unsigned int ID);

        void stopAnimation();

        unsigned int getCurrentAnimation();

        void render(unsigned int offset);

        void render() override;
    };

}