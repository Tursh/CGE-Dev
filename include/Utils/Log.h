#pragma once

#include <IO/Input.h>
#include <iostream>
#include "DebugBreak.h"
#include "ConsoleColor.h"

namespace CGE::Utils
{


// Print information on the console
#define logInfo(msg) std::cout << "[INFO] " << msg << std::endl
// Print warning on the console
#ifdef __MINGW32__
#define logWarning(msg) std::cout << yellow << "[WARNING] " << msg << white << std::endl
#else
#define logWarning(msg) std::cout << "\033[93m[WARNING] " << msg << \
        " - " << __FILE__ << ": " << __LINE__ << "\033[0m" << std::endl;
#endif
// Print error on the console
#ifndef NDEBUG
#ifdef __MINGW32__
#define logError(msg) {std::cout << red << "[ERROR] " << msg << white << std::endl;\
        DebugBreak();}
#else //ifndef __MINGW32__
#define logError(msg) {std::cout << "\033[1;31m[ERROR] " << msg << \
        " - File: " << __FILE__ << " - function: " << __FUNCTION__ << " - Line: " << __LINE__ << "\033[0m" << std::endl;\
        CGE::IO::input::ungrabMouse();\
        debugBreak();}
#endif //ifndef __MINGW32__
#else //ifdef NDEBUG
#ifdef __MINGW32__
#define logError(msg) std::cout << red << "[ERROR] " << msg << white << std::endl;
#else //ifndef __MINGW32__
#define logError(msg) std::cout << "\033[1;31m[ERROR] " << msg << "\033[0m" << std::endl
#endif //ifndef __MINGW32__
#endif    //ifdef NDEBUG

}
