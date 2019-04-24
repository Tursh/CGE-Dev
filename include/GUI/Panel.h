#pragma once

#include <vector>

#include "GUIComponent.h"
#include "Button.h"

namespace CGE::GUI
{
    class Button;

    class Panel : public GUIComponent
    {
        unsigned int type_;
    protected:
        std::vector<std::shared_ptr<Button>> buttons_;
        std::vector<std::shared_ptr<GUIComponent>> components_;

    public:
        std::function<void(int key, int usage)> keyCallback;

        Panel(glm::vec2 position, glm::vec2 dimension, unsigned int type,
              std::function<void(int key, int usage)> keyCallback, bool inGamePanel = false);

        ~Panel();

        void addComponent(std::shared_ptr<GUIComponent> newComponent);

        template<class T, typename ...paramType>
        void createChildComponent(paramType ...params)
        {
            this->addComponent(std::dynamic_pointer_cast<GUIComponent>(std::make_shared<T>(params...)));
        }

        void render(GUIShader *shader) override;

        virtual void checkEvents();

        void resetDisplayScale() override;
    };
}
