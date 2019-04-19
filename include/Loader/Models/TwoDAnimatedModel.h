//
// Created by tursh on 1/24/19.
//

#pragma once

#include <Animation/TextureAnimation.h>
#include "TexturedModel.h"

namespace CGE::Loader
{

    class TwoDAnimatedModel : public TexturedModel
    {
        float sizeScale_;
        unsigned int textureCount_;
        Animations::TextureAnimation *animation_;
    public:

        TwoDAnimatedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture[]> textures,
                          unsigned int textureCount, float size, Animations::TextureAnimation *animation);

        ~TwoDAnimatedModel();

        glm::vec2 getModelSize() override;

        void setIdleAnimation(unsigned int ID);

        void startAnimation(unsigned int ID) override;

        void stopAnimation();

        unsigned int getCurrentAnimation() override;

        void render(unsigned int offset);

        void render() override;
    };

}