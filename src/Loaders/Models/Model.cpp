//
// Created by tursh on 1/23/19.
//

#include <Loader/Models/Model.h>
#include <GL/glew.h>
#include <Utils/GLDebug.h>
#include <Utils/Log.h>

namespace CGE
{
    namespace Loader
    {
        /*
        Model constructor
        VAO: VAO ID
        VBOs: list of VBOs
        vertexCount: number of indices
        */
        Model::Model(unsigned int VAO, std::vector<unsigned int> VBOs, unsigned int vertexCount)
                : VAO(VAO), VBOs(VBOs), vertexCount(vertexCount) {}

        /*Delete model (VAO and VBOs too)*/
        Model::~Model()
        {
            //Delete VAO
            GLCall(glDeleteVertexArrays(1, &VAO));

            //Delete VBOs
            for (unsigned int VBO : VBOs)
            {
                GLCall(glDeleteBuffers(1, &VBO));
            }
        }

        /*Bind model*/
        void Model::bind() const
        {
            GLCall(glBindVertexArray(VAO));
        }

        /*Render model*/
        void Model::render(bool textured) const
        {
            GLCall(glBindVertexArray(VAO));
            GLCall(glEnableVertexAttribArray(0));
            if (textured)
            GLCall(glEnableVertexAttribArray(1));
            GLCall(glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr));
            GLCall(glDisableVertexAttribArray(0));
            if (textured)
            GLCall(glDisableVertexAttribArray(1));
            GLCall(glBindVertexArray(0));
        }


    }
}