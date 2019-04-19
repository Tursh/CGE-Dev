#pragma once

#include <glm/ext/matrix_float4x4.hpp>

#include "Shader/ShaderProgram.h"

namespace CGE::GUI
{
    class GUIShader : public Shader::ShaderProgram
    {
    public:
        GUIShader();

        void getAllUniformLocation() override;

        void setTransformationMatrix(glm::mat4 &matrix);
    };
}
