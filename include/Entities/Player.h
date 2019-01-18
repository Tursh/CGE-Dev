//
// Created by tursh on 1/17/19.
//

#pragma once

#include "Entity.h"

namespace CGE
{
    namespace Entities
    {
        class Player : public Entity
        {
        public:
            void move(float speed);
        };

    }
}

