#pragma once

#include <glm/vec2.hpp>
#include <Loader/Meshes/TexturedMesh.h>
#include "GUIShader.h"

namespace CGE::GUI
{
    enum ComponentType
    {
        IMAGE, PANEL, BUTTON
    };

    class GUIComponent
    {
        ComponentType type_;
    protected:
        GUIComponent *parent_;
        glm::vec2 rawPosition_, rawDimension_;
        glm::vec2 position_, dimension_;
        bool visible_ = true;
        char relativeToParent_;
        std::shared_ptr<Loader::TexturedMesh> texMesh_;

        void prepareRender(GUIShader *shader);

    public:
        GUIComponent(ComponentType type, const glm::vec2 &position, const glm::vec2 &dimension,
                     std::shared_ptr<Loader::TexturedMesh> texMesh, char relativeToParent = 3);

        virtual void render(GUIShader *shader);

        virtual void resetDisplayScale();

        bool isMouseInPanel();

        //Getters setters
        const ComponentType &getType_() const;

        const glm::vec2 &getPosition() const;

        const glm::vec2 &getRawPosition() const;

        virtual void setPosition(const glm::vec2 &position);

        const glm::vec2 &getDimension() const;

        const glm::vec2 &getRawDimension() const;

        virtual void setDimension(const glm::vec2 &dimension);

        const bool &getVisibility() const;

        void setVisibility(const bool &visibility);

        GUIComponent *getParent() const;

        void setParent(GUIComponent *parent);
    };

}
