#include <utility>

//
// Created by tursh on 1/24/19.
//

#include <Loader/Models/TwoDAnimatedModel.h>

namespace CGE
{
    namespace Loader
    {

        TwoDAnimatedModel::TwoDAnimatedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture[]> textures,
                                             unsigned int textureCount, Animations::TextureAnimation *animation)
                : TexturedModel(model, textures), textureCount_(textureCount),
                  animation_(animation) {}

        void TwoDAnimatedModel::startAnimation(unsigned int ID)
        {
            animation_->setCurrentAnimation(ID);
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

    }
}



