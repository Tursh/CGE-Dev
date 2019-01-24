//
// Created by tursh on 1/24/19.
//

#include "Loader/Models/TexturedModel.h"

namespace CGE
{
    namespace Loader
    {
        TexturedModel::TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture)
                : model_(model), texture_(texture) {}

        void TexturedModel::render(unsigned int offset)
        {
            texture_.get()[offset].bind();
            model_->render();
        }

        void TexturedModel::bind()
        {
            texture_->bind();
            model_->bind();
        }

        const unsigned int &TexturedModel::indicesCount()
        {
            return model_->vertexCount;
        }
    }
}