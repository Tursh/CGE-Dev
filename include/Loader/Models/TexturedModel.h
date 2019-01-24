//
// Created by tursh on 1/24/19.
//

#pragma once

#include <Loader/Texture.h>
#include <memory>
#include "Model.h"

namespace CGE
{
    namespace Loader
    {

        class TexturedModel
        {
        protected:
            /*Texture ID pointer*/
            std::shared_ptr<Texture[]> texture_;
            /*Model*/
            std::shared_ptr<Model> model_;
        public:
            TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture[]> texture);

            virtual void render();

            void bind();

            const unsigned int &indicesCount();
        };

    }
}