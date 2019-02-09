#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader/ShaderProgram.h"

namespace CGE
{
	namespace Text
	{

		class TextShader : public Shader::ShaderProgram
		{
		public:
			TextShader();

			void getAllUniformLocation() override;

			void setTextColor(glm::vec3 color);

			void setProjectionMatrix(const glm::mat4 &matrix);
		};

	}
}
