#pragma once

#include <glm/ext/vector_float3.hpp>	//glm::vec3
#include <glm/ext/vector_float4.hpp>	//glm::vec4
#include <glm/ext/matrix_float4x4.hpp>	//glm::mat4

namespace CGE::Shader
	{

		class ShaderProgram
		{
		private:
			const unsigned int program_id_;
		public:
			virtual ~ShaderProgram() = default;

			void start();

			void stop();

			void destroy();

		protected:
			ShaderProgram(const char *vertexShader, const char *fragmentShader, bool isPath = true);

			virtual void getAllUniformLocation() = 0;

			unsigned int getUniformLocation(const char *uniformName);

			//Uniforms
			void loadFloat(const unsigned int &location, const float &value);

			void loadVec3(const unsigned int &location, const glm::vec3 &value);

			void loadVec4(const unsigned int &location, const glm::vec4 &value);

			void loadMat4(const unsigned int &location, const glm::mat4 &value);

		private:
			unsigned int compileShader(const char *shader, unsigned int type);
		};

	}