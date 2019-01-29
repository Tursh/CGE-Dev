//
// Created by tursh on 1/17/19.
//

#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <Loader/Texture.h>
#include <Loader/Models/TexturedModel.h>

namespace CGE
{
    namespace Entities
    {
        struct Entity
        {
            unsigned int ID;
            Loader::TexturedModel *texModel_;
            glm::vec3 position_;
            glm::vec3 rotation_;
            bool visible_;

            explicit Entity(unsigned int texModelID, Loader::TexturedModelType type, glm::vec3 position = glm::vec3(0),
                            glm::vec3 rotation = glm::vec3(0), bool visible = true);

            explicit Entity(Loader::TexturedModel *Model, glm::vec3 position = glm::vec3(0),
                            glm::vec3 rotation = glm::vec3(0), bool visible = true);

            ~Entity();

            void startAnimation(unsigned int animationID);

            glm::mat4 getTransformationMatrix();

            void render();
        };
    }
}
