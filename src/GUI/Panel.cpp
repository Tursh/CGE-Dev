#include <utility>


#include <GUI/Panel.h>
#include <glm/ext/matrix_transform.hpp>
#include <Loader/RessourceManager.h>
#include <IO/Input.h>
#include <GUI/GUIManager.h>

namespace CGE
{
    namespace GUI
    {

        Panel::Panel(const glm::vec2 position, const glm::vec2 dimension, PanelType type,
                     std::function<void(int key, int usage)> keyCallback, bool inGamePanel)
                : GUIComponent(PANEL, position, dimension,
                               (type != PANEL_INVISIBLE) ? Loader::resManager::getTexModel(type) : nullptr),
                  type_(type),
                  keyCallback(std::move(keyCallback))
        {
            if (!inGamePanel) IO::input::addPanel(this);
        }

        Panel::~Panel()
        {
            for (auto button : buttons_)
                delete button;
            IO::input::removePanel(this);
            GUIManager::removeComponent(this);
        }

        void Panel::addComponent(GUIComponent *newComponent)
        {
            switch(newComponent->getType_())
            {
                case BUTTON:
                    newComponent->setParent(this);
                    buttons_.push_back(((Button *)newComponent));
                    break;
                default:
                    newComponent->setParent(this);
                    components_.push_back(newComponent);
            }
        }

        void Panel::render(GUIShader *shader)
        {
            if (!visible_)
                return;

            //Render panel
            if (type_ != PANEL_INVISIBLE)
            {
                GUIComponent::render(shader);
            }

            //Render buttons
            for (auto button : buttons_)
                button->render(shader);
        }

        void Panel::checkEvents()
        {
            if (visible_)
            {
                for (auto button : buttons_)
                    button->checkEvent();
            }
        }

        void Panel::resetDisplayScale()
        {
            GUIComponent::resetDisplayScale();
            for (auto *button : buttons_)
                button->resetDisplayScale();
            for (auto *component : components_)
                component->resetDisplayScale();
        }

    }
}
