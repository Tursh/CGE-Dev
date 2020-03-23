//
// Created by tursh on 1/24/19.
//

#pragma once

#include "Mesh.h"
#include <Loader/Texture.h>
#include <memory>

namespace CGE::Loader
{
    class TexturedMesh
    {
    protected:
        bool threeDimension_;
        SharedTexture texture_;
        SharedMesh mesh_;

    public:
        TexturedMesh(SharedMesh mesh, SharedTexture texture, bool threeDimension);

        virtual void render();

        void bind();

        const unsigned int &indicesCount();

        virtual glm::vec2 getTextureSize();

        /**
         * @return the 3D size of the model
         */
        const glm::vec3 &getMeshSize();

        /**
         * @return Is the textured mesh in 3 dimension
         */
        [[nodiscard]]const bool &isThreeDimension() const;

    };

    typedef std::shared_ptr<TexturedMesh> SharedTexMesh;

}