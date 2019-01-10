#pragma once

#include "IO/Display.h"

namespace CGE
{

    IO::Display *initEngine(const char *name, unsigned int width, unsigned int height, bool resizable = true);

    void stopEngine();

}
