//
// Created by tursh on 3/21/19.
//

#pragma once

#include <GUI/Panel.h>
#include <GUI/Button.h>

namespace CGE::GUI::GUIManager
{
    void init();

    void terminate();

    void addComponent(GUIComponent *newComponent);

    void removeComponent(GUIComponent *component);

    void resetDisplayRes(const glm::ivec2 &newResolution);

    void checkEvents();

    void renderGUI();

    const glm::vec2 &getDisplayScale();

    void clear();
}