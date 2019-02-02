#include "GUI/GUIShader.h"

namespace CGE
{
	namespace GUI
	{

const char* VERTEX_SHADER = R"glsl(
#version 130
in vec4 positions;
in vec2 TexCoords;
out vec2 pass_texCoords;

uniform mat4 transformationMatrix;

void main()
{
	gl_Position = transformationMatrix * positions;
	pass_texCoords = TexCoords;
}
)glsl";

const char* FRAGMENT_SHADER = R"glsl(
#version 130
in vec2 pass_texCoords;
out vec4 color;

uniform sampler2D tex;

void main()
{
	color = texture(tex, pass_texCoords);
	//color = vec4(1.0, 1.0, 1.0, 1.0);
}
)glsl";

		unsigned int transformationMatrixLocation;

		GUIShader::GUIShader()
				: Shader::ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER, false)
		{
			start();
			getAllUniformLocation();
			stop();
		}

		void GUIShader::getAllUniformLocation()
		{
			transformationMatrixLocation = getUniformLocation("transformationMatrix");
		}

		void GUIShader::setTransformationMatrix(glm::mat4& matrix)
		{
			loadMat4(transformationMatrixLocation, matrix);
		}

	}
}
