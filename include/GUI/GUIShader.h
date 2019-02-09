#pragma once
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader/ShaderProgram.h"

namespace CGE
{
	namespace GUI
	{
		class GUIShader : public Shader::ShaderProgram
		{
			glm::mat4 projectionMatrix;
		public:
			GUIShader();
			void getAllUniformLocation() override;
			void setTransformationMatrix(glm::mat4& matrix);
			void setProjectionMatrix(glm::mat4& matrix);
			const glm::mat4 &getProjectionMatrix();
		};
	}
}
