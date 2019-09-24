#include <utility>
#include <Loader/Models/TexturedModel.h>
#include <glm/vec2.hpp>
#include <IO/Window.h>


//
// Created by tursh on 1/24/19.
//

#include "Loader/Models/TexturedModel.h"

namespace CGE::Loader
{
    TexturedModel::TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture,
                                 bool threeDimension)
            : model_(std::move(model)), texture_(std::move(texture)), threeDimension_(threeDimension) {}

    void TexturedModel::render()
    {
        texture_->bind();
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

    bool TexturedModel::isThreeDimension() const
    {
        return threeDimension_;
    }

    glm::vec2 TexturedModel::getTextureSize()
    {
        return texture_->getSize();
    }

    const glm::vec3 &TexturedModel::getModelSize()
    {
        if (model_ != nullptr)
            return model_->size;
        else
            return glm::vec3(0);
    }
}