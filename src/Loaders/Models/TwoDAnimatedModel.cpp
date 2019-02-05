#include <utility>

//
// Created by tursh on 1/24/19.
//

#include <Loader/Models/TwoDAnimatedModel.h>
#include <glm/vec2.hpp>
#include <IO/Display.h>

namespace CGE
{
    namespace Loader
    {

        TwoDAnimatedModel::TwoDAnimatedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture[]> textures,
                                             unsigned int textureCount, float size, Animations::TextureAnimation *animation)
                : TexturedModel(model, textures, Animated2DModel), textureCount_(textureCount),
                  animation_(animation), sizeScale_(size)
        {}

        void TwoDAnimatedModel::startAnimation(unsigned int ID)
        {
            animation_->currentAnimation = ID;
        }

        void TwoDAnimatedModel::render(unsigned int offset)
        {

            texture_[offset].bind();
            model_->render();
        }

        void TwoDAnimatedModel::render()
        {
            texture_[animation_->getTextureToRender()].bind();
            model_->render();
        }

        TwoDAnimatedModel::~TwoDAnimatedModel()
        {
            delete animation_;
        }

        glm::vec2 TwoDAnimatedModel::getModelSize()
        {
            glm::vec2 texSize = texture_[animation_->getTextureToRender()].getSize();
            texSize /= 500;
            texSize *= sizeScale_;
            return texSize;
        }

        unsigned int TwoDAnimatedModel::getCurrentAnimation()
        {
            return animation_->currentAnimation;
        }

        void TwoDAnimatedModel::setIdleAnimation(unsigned int ID)
        {
            animation_->idleAnimation = ID;
        }

        void TwoDAnimatedModel::stopAnimation()
        {
            animation_->returnToIdle();
        }

    }
}



