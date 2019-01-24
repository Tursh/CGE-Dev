//
// Created by tursh on 1/24/19.
//

#pragma once

#include <Animation/TextureAnimation.h>
#include "TexturedModel.h"

namespace CGE
{
    namespace Loader
    {

        class TwoDAnimatedModel : public TexturedModel
        {
            unsigned int textureCount_;
            Animations::TextureAnimation *animation_;
        public:

            TwoDAnimatedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture[]> textures,
                              unsigned int textureCount, Animations::TextureAnimation *animation);

            ~TwoDAnimatedModel();

            void startAnimation(unsigned int ID);

            void render(unsigned int offset);

            void render() override;
        };

    }
}