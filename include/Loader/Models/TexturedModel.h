//
// Created by tursh on 1/24/19.
//

#pragma once

#include "Model.h"
#include <Loader/Texture.h>
#include <memory>

namespace CGE::Loader
{
    class TexturedModel
    {
    protected:
        bool threeDimension_;
        /*Texture pointer*/
        std::shared_ptr<Texture> texture_;
        /*Model*/
        std::shared_ptr<Model> model_;
    public:
        TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, bool threeDimension);

        virtual void render();

        void bind();

        const unsigned int &indicesCount();

        virtual glm::vec2 getTextureSize();

        bool isThreeDimension() const;

    };

}