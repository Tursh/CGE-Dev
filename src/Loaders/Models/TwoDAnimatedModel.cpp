#include <utility>

#include <utility>

//
// Created by tursh on 1/24/19.
//

#include <Loader/Models/TwoDAnimatedModel.h>
#include <glm/vec2.hpp>
#include <IO/Window.h>

namespace CGE::Loader
{

    TwoDAnimatedModel::TwoDAnimatedModel(TexturedModel texturedModel, float size, Animations::TwoDAnimation *animation)
            : TexturedModel(std::move(texturedModel)),
              animation_(animation),
              sizeScale_(size) {}

    void TwoDAnimatedModel::startAnimation(unsigned int ID)
    {
        animation_->setCurrentAnimation(ID);
    }

    void TwoDAnimatedModel::render(unsigned int offset)
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
        model_->setTexCoords(0, texCoordsData);
        model_->render();
    }

    void TwoDAnimatedModel::render()
    {
        model_->render(animation_->getTextureToRender());
    }

    TwoDAnimatedModel::~TwoDAnimatedModel()
    {
        delete animation_;
    }

    glm::vec2 TwoDAnimatedModel::getTextureSize()
    {
        glm::vec2 texSize = texture_->getSize();
        texSize /= 500;
        texSize *= sizeScale_;
        return texSize;
    }

    unsigned int TwoDAnimatedModel::getCurrentAnimation()
    {
        return animation_->getCurrentAnimation();
    }

    void TwoDAnimatedModel::setIdleAnimation(unsigned int ID)
    {
        animation_->setIdleAnimation(ID);
    }

    void TwoDAnimatedModel::stopAnimation()
    {
        animation_->returnToIdle();
    }

}



