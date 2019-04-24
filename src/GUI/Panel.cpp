#include <utility>


#include <GUI/Panel.h>
#include <glm/ext/matrix_transform.hpp>
#include <Loader/RessourceManager.h>
#include <IO/Input.h>
#include <GUI/GUIManager.h>

namespace CGE::GUI
{
    namespace GUIManager
    {
        extern bool GUIGotCleared;
    }

    Panel::Panel(const glm::vec2 position, const glm::vec2 dimension, unsigned int type,
                 std::function<void(int key, int usage)> keyCallback, bool inGamePanel)
            : GUIComponent(PANEL, position, dimension,
                           (type) ? Loader::resManager::getTexModel(type) : nullptr),
              type_(type),
              keyCallback(std::move(keyCallback))
    {
        if (!inGamePanel) IO::input::addPanel(this);
    }

    Panel::~Panel()
    {
        IO::input::removePanel(this);
        GUIManager::removeComponent(this);
    }

    void Panel::addComponent(std::shared_ptr<GUIComponent> newComponent)
    {
        switch (newComponent->getType_())
        {
            case BUTTON:
                newComponent->setParent(this);
                buttons_.push_back(std::dynamic_pointer_cast<Button>(newComponent));
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
        //If type_ == 0, then it is an invisible panel
        if (type_)
            GUIComponent::render(shader);

        //Render buttons
        for (auto &button : buttons_)
            button->render(shader);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        for(auto &component : components_)
            component->render(shader);
        glDisable(GL_BLEND);
    }

    void Panel::checkEvents()
    {
        if (visible_)
        {
            for (auto &button : buttons_)
            {
                if (!GUIManager::GUIGotCleared)
                    button->checkEvent();
            }
        }
    }

    void Panel::resetDisplayScale()
    {
        GUIComponent::resetDisplayScale();
        for (auto &button : buttons_)
            button->resetDisplayScale();
        for (auto &component : components_)
            component->resetDisplayScale();
    }

}
