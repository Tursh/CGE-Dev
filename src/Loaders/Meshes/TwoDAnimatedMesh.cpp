#include <utility>

#include <utility>

//
// Created by tursh on 1/24/19.
//

#include <Loader/Meshes/TwoDAnimatedMesh.h>
#include <glm/vec2.hpp>
#include <IO/Window.h>

namespace CGE::Loader
{

    TwoDAnimatedMesh::TwoDAnimatedMesh(TexturedMesh texturedMesh, float size, Animations::TwoDAnimation *animation)
            : TexturedMesh(std::move(texturedMesh)),
              animation_(animation),
              sizeScale_(size) {}

    void TwoDAnimatedMesh::startAnimation(unsigned int ID)
    {
        animation_->setCurrentAnimation(ID);
    }

    void TwoDAnimatedMesh::render(unsigned int offset)
    {
        texture_->bind();
        glm::vec4 texLimits = texture_->getTextureLimits();
        float texCoords[] =
                {
                        texLimits.x, texLimits.y,
                        texLimits.x, texLimits.w,
                        texLimits.z, texLimits.w,
                        texLimits.z, texLimits.y
                };
        Data<float> texCoordsData(texCoords, 4 * 2);
        mesh_->setTexCoords(0, texCoordsData);
        mesh_->render();
    }

    void TwoDAnimatedMesh::render()
    {
        mesh_->render(animation_->getTextureToRender());
    }

    TwoDAnimatedMesh::~TwoDAnimatedMesh()
    {
        delete animation_;
    }

    glm::vec2 TwoDAnimatedMesh::getTextureSize()
    {
        glm::vec2 texSize = texture_->getSize();
        texSize /= 500;
        texSize *= sizeScale_;
        return texSize;
    }

    unsigned int TwoDAnimatedMesh::getCurrentAnimation()
    {
        return animation_->getCurrentAnimation();
    }

    void TwoDAnimatedMesh::setIdleAnimation(unsigned int ID)
    {
        animation_->setIdleAnimation(ID);
    }

    void TwoDAnimatedMesh::stopAnimation()
    {
        animation_->returnToIdle();
    }

}



