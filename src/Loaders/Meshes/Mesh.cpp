//
// Created by tursh on 1/23/19.
//

#include <Loader/Meshes/Mesh.h>
#include <GL/glew.h>
#include <Utils/GLDebug.h>
#include <Utils/Log.h>
#include <tuple>
#include <utility>

namespace CGE::Loader
{
    /*
    Mesh constructor
    VAO: VAO ID
    VBOs: list of VBOs
    vertexCount: number of indices
    */
    Mesh::Mesh(unsigned int VAO, std::vector<unsigned int> VBOs, unsigned int vertexCount, glm::vec3 size)
            : VAO(VAO), VBOs(std::move(VBOs)), vertexCount(vertexCount), size(size)
    {}

    void trashMesh(const std::tuple<unsigned int, std::vector<unsigned int>> &model);

    /*Delete model (VAO and VBOs too)*/
    Mesh::~Mesh()
    {
        trashMesh(std::make_tuple(VAO, VBOs));
    }

    /*Bind model*/
    void Mesh::bind() const
    {
        GLCall(glBindVertexArray(VAO));
    }

    /*Render model*/
    void Mesh::render(bool textured) const
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

    void Mesh::setTexCoords(unsigned int offset, const Data<float> &data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, data.size_ * sizeof(float), data.data_);
    }


}