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

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * position;
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
	color = texture(tex, passTexCoords);
}
)glsl";

        BasicShader::BasicShader()
                : ShaderProgram(BASICVERTEXSHADER, BASICFRAGMENTSHADER, false)
        {
            getAllUniformLocation();
            //Load blank matrices to not end with nothing on screen if a matrix is not set.
            glm::mat4 defaultMatrix(1);
            start();
            loadMatrix(TRANSFORMATION, defaultMatrix);
            loadMatrix(PROJECTION, defaultMatrix);
            loadMatrix(VIEW, defaultMatrix);
            stop();
        }


        void BasicShader::getAllUniformLocation()
        {
            transformationMatrixLocation = getUniformLocation("transformationMatrix");
            projectionMatrixLocation = getUniformLocation("projectionMatrix");
            viewMatrixLocation = getUniformLocation("viewMatrix");
        }

        void BasicShader::loadMatrix(CGE::Shader::MatrixType type, glm::mat4 matrix)
        {
            switch (type)
            {
                case TRANSFORMATION:
                    loadMat4(transformationMatrixLocation, matrix);
                    break;
                case PROJECTION:
                    loadMat4(projectionMatrixLocation, matrix);
                    break;
                case VIEW:
                    loadMat4(viewMatrixLocation, matrix);
                    break;
            }
        }
    }
}