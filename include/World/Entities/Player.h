//
// Created by tursh on 1/17/19.
//

#pragma once

#include <View/Camera.h>
#include <World/Entities/Entity.h>
#include <World/Terrain/Terrain.h>

namespace CGE
{
    namespace View
    {
        class Camera;
    }
    namespace Entities
    {
        class Player : public Entity
        {
            bool twoD_;

            View::Camera *camera_;
        public:
            explicit Player(unsigned int texModelID, Loader::TexturedModelType type, bool twoD = false);

            explicit Player(Loader::TexturedModel *texModel, bool twoD = false);
            void move(float speed, Terrain::Terrain *terrain);

            View::Camera *getCamera();

            bool isTwoD();
        };

    }
}

