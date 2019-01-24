//
// Created by tursh on 1/24/19.
//

#pragma once

#include <Loader/Texture.h>

namespace CGE
{
    namespace Loader
    {


        class TexturedModel
        {
            /*Texture ID pointer*/
            std::shared_ptr<Texture> texture_;
            /*Model*/
            std::shared_ptr<Model> model_;
        public:
            TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture);

            void render(unsigned int offset = 0);

            void bind();

            const unsigned int &indicesCount();
        };

    }
}