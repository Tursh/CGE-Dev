#pragma once

#include <vector>
#include <Loader/Loader.h>
#include <glm/glm.hpp>

namespace CGE::Loader
{

    /*
    Basic Mesh containing the shape of a 2D or 3D model
    VAO: ID of the VAO
    */
    class Mesh
    {
        const unsigned int VAO;
        const std::vector<unsigned int> VBOs;
    public:
        const unsigned int vertexCount;
        const glm::vec3 size;

        /*
        Mesh constructor
        VAO: VAO ID
        VBOs: list of VBOs
        vertexCount: number of indices
        */
        Mesh(unsigned int VAO, std::vector<unsigned int> VBOs, unsigned int vertexCount, glm::vec3 size);

        /*Delete model (VAO and VBOs too)*/
        ~Mesh();

        /*Bind model*/
        void bind() const;

        /*Render model*/
        void render(bool textured = true) const;

        void setTexCoords(unsigned int offset, const Data<float> &data);
    };


}