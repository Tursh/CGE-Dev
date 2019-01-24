//
// Created by tursh on 1/17/19.
//

#pragma once

#include <View/Camera.h>
#include <World/Entities/Entity.h>

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
            View::Camera *camera_;
        public:
            Player(unsigned int texModelID);

            Player(Loader::TexturedModel texModel);
            void move(float speed);

            glm::mat4 getViewMatrix();
        };

    }
}

