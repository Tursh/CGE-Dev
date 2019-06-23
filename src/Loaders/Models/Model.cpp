//
// Created by tursh on 1/23/19.
//

#include <Loader/Models/Model.h>
#include <GL/glew.h>
#include <Utils/GLDebug.h>
#include <Utils/Log.h>
#include <tuple>

namespace CGE::Loader
{
    /*
    Model constructor
    VAO: VAO ID
    VBOs: list of VBOs
    vertexCount: number of indices
    */
    Model::Model(unsigned int VAO, std::vector<unsigned int> VBOs, unsigned int vertexCount, glm::vec3 size)
            : VAO(VAO), VBOs(VBOs), vertexCount(vertexCount), size(size) {}

    void trashModel(std::tuple<unsigned int, std::vector<unsigned int>> model);

    /*Delete model (VAO and VBOs too)*/
    Model::~Model()
    {
        trashModel(std::make_tuple(VAO, VBOs));
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

    void Model::setTexCoords(unsigned int offset, const Data<float> &data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, data.size * sizeof(float), data.data);
    }


}