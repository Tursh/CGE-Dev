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
        /**
         * Transformation and view matrix
         */
        glm::mat4 transformationMatrix_ = glm::mat4(1),
                viewMatrix_ = glm::mat4(1);

        /**
         * Custom projection matrix
         */
        bool useCustomProjectionMatrix_ = false;
        glm::mat4 customProjectionMatrix_ = glm::mat4(1);

        /**
         * Window projection matrix
         */
        const glm::mat4 &projectionMatrix_;

        /**
         * Uniform location
         */
        unsigned int TVPMatrixLocation_ = 0;

        /**
         * Get all the uniform location in shader during the  initialisation
         */
        void getAllUniformLocation() override;

    protected:
        /**
         * Create a custom shader
         * @param vertexShader The vertex shader
         * @param fragmentShader The fragment shader
         * @param isPath Are the shaders are path to files or the shader loaded in char pointers
         * @param windowID The window ID to get the projection matrix
         */
        BasicShader(const char *vertexShader, const char *fragmentShader, bool isPath = true,
                    unsigned int windowID = 0);

    public:
        /**
         * Create a basic shader
         * @param windowID The window ID to get the projection matrix
         */
        explicit BasicShader(unsigned int windowID = 0);

        /**
         * Load a transformation, view or projection matrix
         * If you load a projection matrix, you stop using the window one (SEE CGE::IO::Window)
         * @param type TRANSFORMATION, VIEW or PROJECTION
         * @param matrix The matrix to load
         */
        void loadMatrix(MatrixType type, glm::mat4 matrix);
    };


}

