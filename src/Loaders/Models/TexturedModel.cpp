#include <utility>

//
// Created by tursh on 1/24/19.
//

#include "Loader/Models/TexturedModel.h"

namespace CGE
{
    namespace Loader
    {
        TexturedModel::TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture[]> texture)
                : model_(std::move(model)), texture_(std::move(texture)) {}

        void TexturedModel::render()
        {
            texture_[0].bind();
            model_->render();
        }

        void TexturedModel::bind()
        {
            texture_[0].bind();
            model_->bind();
        }

        const unsigned int &TexturedModel::indicesCount()
        {
            return model_->vertexCount;
        }
    }
}