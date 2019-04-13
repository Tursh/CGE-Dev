//
// Created by tursh on 3/21/19.
//

#include <GUI/GUIManager.h>
#include <IO/Display.h>

namespace CGE::GUI::GUIManager
{
    bool GUIGotCleared = false;
    bool singleDelete = true;

    GUIShader *shader;
    glm::vec2 displayScale(1);

    std::vector<GUIComponent *> components;
    std::vector<Panel *> panels;
    std::vector<Button *> buttons;

    void init()
    {
        shader = new GUIShader;
    }

    void terminate()
    {
        shader->destroy();
        clear();
    }

    void resetDisplayRes(const glm::ivec2 &newResolution)
    {
        displayScale = glm::vec2((float) newResolution.x / CGE::IO::DEFAULT_WIDTH,
                                 (float) newResolution.y / CGE::IO::DEFAULT_HEIGHT);
        for (auto *panel : panels)
            panel->resetDisplayScale();
        for (auto *button : buttons)
            button->resetDisplayScale();
        for (auto *component : components)
            component->resetDisplayScale();
    }

    void checkEvents()
    {
        GUIGotCleared = false;
        for (auto *panel : panels)
            panel->checkEvents();
        for (auto *button : buttons)
            button->checkEvent();
    }

    void renderGUI()
    {
        GUIGotCleared = false;
        for (auto *panel : panels)
            panel->render(shader);
        for (auto *button : buttons)
            button->render(shader);
        for (auto *component : components)
            component->render(shader);
    }

    const glm::vec2 &getDisplayScale()
    {
        return displayScale;
    }

    void addComponent(GUIComponent *newComponent)
    {
        switch (newComponent->getType_())
        {
            case BUTTON:
                buttons.push_back(((Button *) newComponent));
                break;
            case PANEL:
                panels.push_back(((Panel *) newComponent));
                break;
            case IMAGE:
                components.push_back(newComponent);
                break;
            default:
                components.push_back(newComponent);
        }
    }

    void removeComponent(GUIComponent *component)
    {
        if (singleDelete)
            switch (component->getType_())
            {
                case PANEL:
                    panels.erase(remove(panels.begin(), panels.end(), ((Panel *) component)), panels.end());
                    break;
                case BUTTON:
                    buttons.erase(remove(buttons.begin(), buttons.end(), ((Button *) component)),
                                  buttons.end());
                    break;
                case IMAGE:
                    components.erase(remove(components.begin(), components.end(), component), components.end());
                    break;
                default:
                    components.erase(remove(components.begin(), components.end(), component), components.end());
            }
    }

    void clear()
    {
        singleDelete = false;
        for (auto *panel : panels)
            delete panel;
        for (auto *button : buttons)
            delete button;
        for (auto *component : components)
            delete component;
        singleDelete = true;

        panels.clear();
        buttons.clear();
        components.clear();

        GUIGotCleared = true;
    }
}