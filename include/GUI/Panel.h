#pragma once

#include <vector>

#include "GUIComponent.h"
#include "Button.h"

namespace CGE
{
    namespace GUI
    {
        enum PanelType
        {
            PANEL_INVISIBLE, PANEL_DEFAULT = 20000
        };

        class Button;

        class Panel : public GUIComponent
        {
            PanelType type_;
            Loader::TexturedModel *texModel_;
        protected:
            std::vector<Button *> buttons_;

        public:
            std::function<void(int key, int usage)> keyCallback;

            Panel(glm::vec2 position, glm::vec2 dimension, PanelType type,
                  std::function<void(int key, int usage)> keyCallback);

            ~Panel();

            void addButton(Button *newButton);

            void draw();

            void checkEvents();
        };
    }
}
