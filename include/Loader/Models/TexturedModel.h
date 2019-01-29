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

        enum TexturedModelType
        {
            BasicTexturedModel, Animated3DModel, Animated2DModel
        };

        class TexturedModel
        {
        protected:
            TexturedModelType type_;
            /*Texture ID pointer*/
            std::shared_ptr<Texture[]> texture_;
            /*Model*/
            std::shared_ptr<Model> model_;
        public:
            TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture[]> texture, TexturedModelType type);

            TexturedModelType getType();

            virtual void render();

            void bind();

            const unsigned int &indicesCount();

            //TODO: remove start animation and get current animation function from TexturedModel
            virtual unsigned int getCurrentAnimation(){return 0;}

            virtual void startAnimation(unsigned int ID) {}

            virtual glm::vec2 getModelSize();
        };

    }
}