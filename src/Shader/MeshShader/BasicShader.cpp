//
// Created by tursh on 1/6/19.
//

#include <Utils/Log.h>
#include <Shader/MeshShader/BasicShader.h>
#include <IO/Window.h>

namespace CGE::Shader
{

    const char *BASIC_VERTEX_SHADER = R"glsl(
#version 130
in vec4 in_position;
in vec2 in_texCoords;
out vec2 passTexCoords;

uniform mat4 TVP;

void main()
{
	gl_Position = TVP * in_position;
	passTexCoords = in_texCoords;
}
)glsl";

    const char *BASIC_FRAGMENT_SHADER = R"glsl(
#version 130
in vec2 passTexCoords;
out vec4 color;

uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, passTexCoords);
    //If the alpha is under 0.1 don't draw anything
    if(texColor.a < 0.1)
        discard;
	color = texColor;
}
)glsl";

    void BasicShader::getAllUniformLocation()
    {
        TVPMatrixLocation_ = getUniformLocation("TVP");
    }

    BasicShader::BasicShader(unsigned int windowID)
            : ShaderProgram(BASIC_VERTEX_SHADER, BASIC_FRAGMENT_SHADER, false),
              projectionMatrix_(IO::getWindow(windowID)->getProjectionMatrix())
    {
        //Get uniform location
        getAllUniformLocation();

        //Load blank matrices to not end with nothing on screen if a matrix is not set.
        start();
        glm::mat4 MVP = projectionMatrix_ * viewMatrix_ * transformationMatrix_;
        loadMat4(TVPMatrixLocation_, MVP);
        stop();
    }

    BasicShader::BasicShader(const char *vertexShader, const char *fragmentShader, bool isPath, unsigned int windowID)
            : ShaderProgram(
            vertexShader, fragmentShader, isPath), projectionMatrix_(IO::getWindow(windowID)->getProjectionMatrix())
    {
        getAllUniformLocation();
        //Load blank matrices to not end with nothing on screen if a matrix is not set.
        start();
        glm::mat4 MVP = projectionMatrix_ * viewMatrix_ * transformationMatrix_;
        loadMat4(TVPMatrixLocation_, MVP);
        stop();
    }

    void BasicShader::loadMatrix(CGE::Shader::MatrixType type, glm::mat4 matrix)
    {
        switch (type)
        {
            case TRANSFORMATION:
                transformationMatrix_ = matrix;
                break;
            case VIEW:
                viewMatrix_ = matrix;
                break;
            case PROJECTION:
                customProjectionMatrix_ = matrix;
                if (!useCustomProjectionMatrix_)
#ifndef NDEBUG
                    logWarning(
                            "By loading a projection matrix, you decide to not use the projection matrix of your window");

#endif
                useCustomProjectionMatrix_ = true;
                break;
        }

        glm::mat4 MVP = (useCustomProjectionMatrix_ ? customProjectionMatrix_ : projectionMatrix_)
                        * viewMatrix_ * transformationMatrix_;
        loadMat4(TVPMatrixLocation_, MVP);
    }

}