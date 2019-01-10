/*
Help Debug OpenGL by detecting if an openGL occured
Author: Raphael Tremblay
*/

#include "DebugBreak.h"
#include <assert.h>

#pragma once

namespace CGE
{
    namespace Utils
    {

//Clear error from openGL error buffer
        void GLClearError();

/*
Log OpenGL error
function: Function name (#function)
file: File where the error was produced (__FILE__)
line: Line where the error was produced (__LINE__)
*/
        bool GLLogCall(const char *function, const char *file, int line);

/*If there is an error, break*/
#define ASSERT(x) if (!(x)) debugBreak();
/*If in debug mode check for errors*/
#ifndef NDEBUG
        /*
        Call OpenGL function and check if there is an error produced
        x: function to call
        */
#define GLCall(x) {CGE::Utils::GLClearError();\
    x;\
    ASSERT(CGE::Utils::GLLogCall(#x, __FILE__, __LINE__))}
#else
#define GLCall(x) x
#endif


    }
}
