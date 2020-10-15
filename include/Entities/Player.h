/*
 * Player.h
 *
 * Created by tursh on 10/15/20.
*/

#pragma once

#include <Entities/Entity.h>
#include <View/Camera.h>

namespace CGE::Entities
{

    class Player : public CGE::Entities::Entity
    {
        CGE::View::Camera &camera_;
    public:
        explicit Player(unsigned int texMeshID, CGE::View::Camera &camera);

        explicit Player(CGE::Loader::TexturedMesh *texMesh, CGE::View::Camera &camera,
                        glm::vec3 position = glm::vec3(0),
                        glm::vec3 rotation = glm::vec3(0));

        void move(float speed);

        const glm::vec3 &getSize() override;
    };

}

