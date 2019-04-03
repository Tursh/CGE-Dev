#pragma once

#include <vector>

#include "GUIComponent.h"
#include "Button.h"

namespace CGE
{
    namespace GUI
    {
        class Button;

        class Panel : public GUIComponent
        {
            unsigned int type_;
        protected:
            std::vector<Button *> buttons_;
            std::vector<GUIComponent *> components_;

        public:
            std::function<void(int key, int usage)> keyCallback;

            Panel(glm::vec2 position, glm::vec2 dimension, unsigned int type,
                  std::function<void(int key, int usage)> keyCallback, bool inGamePanel = false);

            ~Panel();

            void addComponent(GUIComponent *newComponent);

            virtual void render(GUIShader *shader) override;

            void checkEvents();

            void resetDisplayScale() override;
        };
    }
}
