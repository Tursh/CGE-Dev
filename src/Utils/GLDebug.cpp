/*
Help Debug OpenGL by detecting if an openGL occured
Author: Raphael Tremblay
*/

#include <GL/glew.h>    //GL*

#include "Utils/Log.h"        //logWarning

namespace CGE::Utils
{

//Clear error from openGL error buffer
    void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

/*
Log error
function: Funtion name (#function)
file: File where the error was produced (__FILE__)
line: Line where the error was produced (__LINE__)
*/
    bool GLLogCall(const char *function, const char *file, int line)
    {
        while (const GLenum error = glGetError())
        {
            logWarning(" [OpenGL Error] (" << std::hex << error << "): " << function <<
                                           " " << file << ":" << line << '\n' << "Error message: "
                                           << glewGetErrorString(error));
            return false;
        }
        return true;
    }

}