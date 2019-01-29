//
// Created by tursh on 1/6/19.
//

#include <Shader/ModelShader/BasicShader.h>

namespace CGE
{
    namespace Shader
    {

        const char *BASICVERTEXSHADER = R"glsl(
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;
out vec2 passTexCoords;

uniform mat4 TVP;

void main()
{
	gl_Position = TVP * position;
	passTexCoords = texCoords;
}
)glsl";

        const char *BASICFRAGMENTSHADER = R"glsl(
#version 330 core
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

        BasicShader::BasicShader()
                : ShaderProgram(BASICVERTEXSHADER, BASICFRAGMENTSHADER, false), transformationMatrix_(1),
                  viewMatrix_(1), projectionMatrix_(1)
        {
            getAllUniformLocation();
            //Load blank matrices to not end with nothing on screen if a matrix is not set.
            start();
            glm::mat4 MVP = projectionMatrix_ * viewMatrix_ * transformationMatrix_;
            loadMat4(TVPMatrixLocation_, MVP);
            stop();
        }

        BasicShader::BasicShader(const char *vertexShader, const char *fragmentShader, bool isPath) : ShaderProgram(
                vertexShader, fragmentShader, isPath), transformationMatrix_(1), viewMatrix_(1), projectionMatrix_(1)
        {
            getAllUniformLocation();
            //Load blank matrices to not end with nothing on screen if a matrix is not set.
            start();
            glm::mat4 MVP = projectionMatrix_ * viewMatrix_ * transformationMatrix_;
            loadMat4(TVPMatrixLocation_, MVP);
            stop();
        }

        void BasicShader::getAllUniformLocation()
        {
            TVPMatrixLocation_ = getUniformLocation("TVP");
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
                    projectionMatrix_ = matrix;
                    break;
            }
            glm::mat4 MVP = projectionMatrix_ * viewMatrix_ * transformationMatrix_;
            loadMat4(TVPMatrixLocation_, MVP);
        }

    }
}