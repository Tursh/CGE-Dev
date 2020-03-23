#pragma once

#include "IO/Window.h"

namespace CGE
{

	/**
	 * Initialize the library and it's dependencies then return the main window
	 * @param name Your application name
	 * @param width The window width_
	 * @param height The window height
	 * @param resizable If the window will be resizable
	 * @return The window (can be access by CGE::IO::getWindow(0)
	 */
    IO::Window *initEngine(const char *name,
                           unsigned int width = IO::DEFAULT_WIDTH,
                           unsigned int height = IO::DEFAULT_HEIGHT,
                           bool resizable = true);

    /**
     * Terminate the library and dependencies
     */
    void stopEngine();

}
