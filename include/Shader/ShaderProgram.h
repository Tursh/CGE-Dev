#pragma once

#include <glm/ext/vector_float3.hpp>    //glm::vec3
#include <glm/ext/vector_float4.hpp>    //glm::vec4
#include <glm/ext/matrix_float4x4.hpp>    //glm::mat4

namespace CGE::Shader
{

    class ShaderProgram
    {
    private:
        const unsigned int programId_;
    public:
        virtual ~ShaderProgram() = default;

        /**
         * Start using the shader program
         */
        void start();

        /**
         * Stop using the shader program
         */
        void stop();

        /**
         * Free the shader program in GPU
         */
        void destroy();

        /**
         * @return Is this shader started
         */
        bool isBeingUsed();

    protected:
        /**
         * Load a shader program
         * @param vertexShader The vertex shader
         * @param fragmentShader The fragment shader
         * @param isPath Are the shaders are path to files or the shader loaded in char pointers
         */
        ShaderProgram(const char *vertexShader, const char *fragmentShader, bool isPath = true);

        /**
         * Place to get your uniform location
         */
        virtual void getAllUniformLocation() = 0;

        /**
         * Get an uniform location
         * @param uniformName The exact name as in the your shader program
         * @return The location
         */
        unsigned int getUniformLocation(const char *uniformName);

        //Uniforms load
        void loadFloat(const unsigned int &location, const float &value);

        void loadVec3(const unsigned int &location, const glm::vec3 &value);

        void loadVec4(const unsigned int &location, const glm::vec4 &value);

        void loadMat4(const unsigned int &location, const glm::mat4 &value);

    private:
        /**
         * Compile a shader and load it into the GPU
         * @param shader The loaded shader into a const char pointer
         * @param type GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
         * @return The shader ID ready to be attached to a shader program
         */
        static unsigned int compileShader(const char *shader, unsigned int type);
    };

}