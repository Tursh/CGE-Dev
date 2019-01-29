#include <utility>
#include <Loader/Models/TexturedModel.h>
#include <glm/vec2.hpp>
#include <IO/Display.h>


//
// Created by tursh on 1/24/19.
//

#include "Loader/Models/TexturedModel.h"

namespace CGE
{
    namespace Loader
    {
        TexturedModel::TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture[]> texture, TexturedModelType type)
                : model_(std::move(model)), texture_(std::move(texture)), type_(type) {}

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

        TexturedModelType TexturedModel::getType()
        {
            return type_;
        }

        glm::vec2 TexturedModel::getModelSize()
        {
            glm::vec2 texSize = texture_[0].getSize();
            texSize.x /= IO::DEFAULT_WIDTH;
            texSize.y /= IO::DEFAULT_HEIGHT;
            return texSize;
        }
    }
}