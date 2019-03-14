
#include <GUI/GUIShader.h>

#include "GUI/GUIShader.h"

namespace CGE
{
    namespace GUI
    {

        const char *VERTEX_SHADER = R"glsl(
#version 130
in vec4 positions;
in vec2 TexCoords;
out vec2 pass_texCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

void main()
{
	gl_Position = (projectionMatrix * transformationMatrix) * positions;
	pass_texCoords = TexCoords;
}
)glsl";

        const char *FRAGMENT_SHADER = R"glsl(
#version 130
in vec2 pass_texCoords;
out vec4 color;

uniform sampler2D tex;

void main()
{
	vec4 texColor = texture(tex, pass_texCoords);
    //If the alpha is under 0.1 don't draw anything
    if(texColor.a < 0.1)
        discard;
	color = texColor;
}
)glsl";

        unsigned int transformationMatrixLocation,
                projectionMatrixLocation;

        GUIShader::GUIShader()
                : Shader::ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER, false), projectionMatrix(1)
        {
            start();
            getAllUniformLocation();
            stop();
        }

        void GUIShader::getAllUniformLocation()
        {
            transformationMatrixLocation = getUniformLocation("transformationMatrix");
            projectionMatrixLocation = getUniformLocation("projectionMatrix");
        }

        void GUIShader::setTransformationMatrix(glm::mat4 &matrix)
        {
            loadMat4(transformationMatrixLocation, matrix);
        }

        void GUIShader::setProjectionMatrix(glm::mat4 &matrix)
        {
            loadMat4(projectionMatrixLocation, matrix);
            projectionMatrix = matrix;
        }

        const glm::mat4 &GUIShader::getProjectionMatrix()
        {
            return projectionMatrix;
        }


    }
}
