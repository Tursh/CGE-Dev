#include <utility>


#include <GUI/Panel.h>
#include <GUI/GUIRenderer.h>
#include <glm/ext/matrix_transform.hpp>
#include <Loader/RessourceManager.h>
#include <IO/Input.h>

namespace CGE
{
    namespace GUI
    {

        Panel::Panel(const glm::vec2 position, const glm::vec2 dimension, PanelType type,
                     std::function<void(int key, int usage)> keyCallback, bool inGamePanel)
                : GUIComponent(position, dimension,
                               (type != PANEL_INVISIBLE) ? Loader::resManagement::getTexModel(type) : nullptr),
                  type_(type),
                  keyCallback(std::move(keyCallback))
        {
            if (!inGamePanel) IO::input::addPanel(this);
        }

        Panel::~Panel()
        {
            for (auto button : buttons_)
                delete button;
            if (type_ != PANEL_INVISIBLE)
                delete texModel_;
            IO::input::removePanel(this);
        }

        void Panel::addButton(Button *newButton)
        {
            newButton->setParent(this);
            buttons_.push_back(newButton);
        }

        void Panel::render()
        {
            if (visible_)
            {
                if (type_ != PANEL_INVISIBLE)
                    GUIRenderer::render(this);

                //Render buttons
                for (auto button : buttons_)
                    button->draw();
            }
        }

        void Panel::checkEvents()
        {
            if (visible_)
            {
                for (auto button : buttons_)
                    button->checkEvent();
            }
        }

        void Panel::draw()
        {
            texModel_->render();
        }
    }
}
