#include <GL/glew.h>                    //GL*
#include <glm/ext/vector_float3.hpp>    //glm::vec3
#include <glm/ext/vector_float4.hpp>    //glm::vec4
#include <glm/ext/matrix_float4x4.hpp>    //glm::mat4
#include <glm/gtc/type_ptr.hpp>            //glm::valueptr

#include "Shader/ShaderProgram.h"
#include "Utils/GLDebug.h"                    //GLCall
#include "Utils/Log.h"                        //logError
#include "Utils/FileManager.h"                //openWholeFile

namespace CGE::Shader
{

    ShaderProgram::ShaderProgram(const char *vertexShader, const char *fragmentShader, bool isPath)
            : program_id_(glCreateProgram())
    {
        unsigned int vertexShaderID, fragmentShaderID;
        if (isPath)
        {
            vertexShader = Utils::readWholeFile(vertexShader);
            fragmentShader = Utils::readWholeFile(fragmentShader);
        }
        vertexShaderID = compileShader(vertexShader, GL_VERTEX_SHADER);
        fragmentShaderID = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

        GLCall(glAttachShader(program_id_, vertexShaderID));
        GLCall(glAttachShader(program_id_, fragmentShaderID));
        GLCall(glLinkProgram(program_id_));
        GLCall(glValidateProgram(program_id_));

        GLCall(glDeleteShader(vertexShaderID));
        GLCall(glDeleteShader(fragmentShaderID));
    }

    void ShaderProgram::start()
    {
        GLCall(glUseProgram(program_id_));
    }

    void ShaderProgram::stop()
    {
        GLCall(glUseProgram(0));
    }

    void ShaderProgram::destroy()
    {
        GLCall(glDeleteProgram(program_id_));
    }

    unsigned int ShaderProgram::getUniformLocation(const char *uniformName)
    {
        unsigned int location;
        GLCall(location = glGetUniformLocation(program_id_, uniformName));
        if (location == 0xffffffff)
        logError(uniformName << " is not a uniform");
        return location;
    }

    void ShaderProgram::loadFloat(const unsigned int &location, const float &value)
    {
        GLCall(glUniform1f(location, value));
    }

    void ShaderProgram::loadVec3(const unsigned int &location, const glm::vec3 &value)
    {
        GLCall(glUniform3fv(location, 1, glm::value_ptr(value)));
    }

    void ShaderProgram::loadVec4(const unsigned int &location, const glm::vec4 &value)
    {
        GLCall(glUniform4fv(location, 1, glm::value_ptr(value)));
    }

    void ShaderProgram::loadMat4(const unsigned int &location, const glm::mat4 &value)
    {
        GLCall(glUniformMatrix4fv(location, 1, false, glm::value_ptr(value)));
    }

    unsigned int ShaderProgram::compileShader(const char *shader, unsigned int type)
    {

        //Compile shader
        unsigned int id = glCreateShader(type);
        //Load the source
        GLCall(glShaderSource(id, 1, &shader, nullptr));
        //Compile
        GLCall(glCompileShader(id));

        int result;
        //Check the result of the compilation
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        //If the shader could not compile correctly, log it
        if (result == GL_FALSE)
        {
            int length;
            //Get the length of the error message
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char *message = new char[length];
            //Get the message
            GLCall(glGetShaderInfoLog(id, length, &length, message));
            //Log the message
            logError(
                    "Failed to compile the " << ((type == GL_VERTEX_SHADER) ? "vertex shader!" : "fragment shader!")
                                             << "\nMessage: " << message);
            //Delete the shader that was compiling
            GLCall(glDeleteShader(id));
        }

        return id;
    }

}