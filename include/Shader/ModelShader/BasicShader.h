//
// Created by tursh on 1/6/19.
//

#pragma once

#include <Shader/ShaderProgram.h>

namespace CGE
{
    namespace Shader
    {

        enum MatrixType
        {
            TRANSFORMATION, PROJECTION, VIEW
        };

        class BasicShader : public ShaderProgram
        {
            unsigned int transformationMatrixLocation = 0;
            unsigned int projectionMatrixLocation = 0;
            unsigned int viewMatrixLocation = 0;
            void getAllUniformLocation() override;
        public:
            BasicShader();
            void loadMatrix(MatrixType type, glm::mat4 matrix);
        };


    }
}

