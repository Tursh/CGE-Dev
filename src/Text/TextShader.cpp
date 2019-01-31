#include <Text/TextShader.h>


namespace CGE
{
    namespace Text
    {

        const char *VERTEX_SHADER = R"glsl(
#version 130
in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

void main()
{
	gl_Position = vec4(vertex.xy, 0.0, 1.0);
	TexCoords = vertex.zw;
}
)glsl";

        const char *FRAGMENT_SHADER = R"glsl(
#version 130
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
	color = vec4(textColor, 1.0) * sampled;
}
)glsl";

        unsigned int textColorLocation;

        TextShader::TextShader()
                : ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER, false)
        {
            start();
            getAllUniformLocation();
            stop();
        }

        void TextShader::getAllUniformLocation()
        {
            textColorLocation = getUniformLocation("textColor");
        }

        void TextShader::setTextColor(glm::vec3 color)
        {
            loadVec3(textColorLocation, color);
        }

    }
}
