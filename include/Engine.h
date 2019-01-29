#pragma once

#include "IO/Display.h"

namespace CGE
{

    IO::Display *
    initEngine(const char *name, unsigned int width = IO::DEFAULT_WIDTH, unsigned int height = IO::DEFAULT_HEIGHT,
               bool resizable = true);

    void stopEngine();

}
