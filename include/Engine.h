#pragma once

#include "IO/Window.h"

namespace CGE
{

    IO::Window *initEngine(const char *name,
                           unsigned int width = IO::DEFAULT_WIDTH,
                           unsigned int height = IO::DEFAULT_HEIGHT,
                           bool resizable = true);

    void stopEngine();

}
