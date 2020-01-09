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
    TexturedModel::TexturedModel(SharedMesh mesh,
                                 SharedTexture texture,
                                 bool threeDimension)
            : mesh_(std::move(mesh)),
              texture_(std::move(texture)),
              threeDimension_(threeDimension) {}

    void TexturedModel::render()
    {
        texture_->bind();
        if (mesh_ != nullptr)
            mesh_->render();
    }

    void TexturedModel::bind()
    {
        texture_->bind();
        mesh_->bind();
    }

    const unsigned int &TexturedModel::indicesCount() { return mesh_->vertexCount; }

    bool TexturedModel::isThreeDimension() const { return threeDimension_; }

    glm::vec2 TexturedModel::getTextureSize() { return texture_->getSize(); }

    static auto zero = glm::vec3(0);

    const glm::vec3 &TexturedModel::getModelSize()
    {
        if (mesh_ != nullptr)
            return mesh_->size;
        else
            return zero;
    }
}