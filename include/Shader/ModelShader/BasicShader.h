//
// Created by tursh on 1/6/19.
//

#pragma once

#include <Shader/ShaderProgram.h>

namespace CGE::Shader
{

    enum MatrixType
    {
        TRANSFORMATION, PROJECTION, VIEW
    };

    class BasicShader : public ShaderProgram
    {
        glm::mat4 transformationMatrix_, viewMatrix_, projectionMatrix_;
        unsigned int TVPMatrixLocation_ = 0;

        void getAllUniformLocation() override;

    protected:
        BasicShader(const char *vertexShader, const char *fragmentShader, bool isPath = true);

    public:
        BasicShader();

        void loadMatrix(MatrixType type, glm::mat4 matrix);
    };


}

