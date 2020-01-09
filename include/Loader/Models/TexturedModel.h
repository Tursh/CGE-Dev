//
// Created by tursh on 1/24/19.
//

#pragma once

#include "Mesh.h"
#include <Loader/Texture.h>
#include <memory>

namespace CGE::Loader
{
    class TexturedModel
    {
    protected:
        bool threeDimension_;
        SharedTexture texture_;
        SharedMesh mesh_;

    public:
        TexturedModel(SharedMesh mesh, SharedTexture texture, bool threeDimension);

        virtual void render();

        void bind();

        const unsigned int &indicesCount();

        virtual glm::vec2 getTextureSize();

        /**
         * @return the 3D size of the model
         */
        const glm::vec3 &getModelSize();

        bool isThreeDimension() const;

    };

    typedef std::shared_ptr<TexturedModel> SharedTexModel;

}