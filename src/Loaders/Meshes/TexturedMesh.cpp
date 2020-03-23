#include <utility>
#include <Loader/Meshes/TexturedMesh.h>
#include <glm/vec2.hpp>
#include <IO/Window.h>


//
// Created by tursh on 1/24/19.
//

#include "Loader/Meshes/TexturedMesh.h"

namespace CGE::Loader
{
    TexturedMesh::TexturedMesh(SharedMesh mesh,
                               SharedTexture texture,
                               bool threeDimension)
            : mesh_(std::move(mesh)),
              texture_(std::move(texture)),
              threeDimension_(threeDimension) {}

    void TexturedMesh::render()
    {
        texture_->bind();
        if (mesh_ != nullptr)
            mesh_->render();
    }

    void TexturedMesh::bind()
    {
        texture_->bind();
        mesh_->bind();
    }

    const unsigned int &TexturedMesh::indicesCount() { return mesh_->vertexCount; }

    const bool &TexturedMesh::isThreeDimension() const { return threeDimension_; }

    glm::vec2 TexturedMesh::getTextureSize() { return texture_->getSize(); }

    static auto zero = glm::vec3(0);

    const glm::vec3 &TexturedMesh::getMeshSize()
    {
        if (mesh_ != nullptr)
            return mesh_->size;
        else
            return zero;
    }
}