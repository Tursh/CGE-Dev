#pragma once

#include <vector>

namespace CGE::Loader
{

    /*
    Basic Model containing the shape of a 2D or 3D model
    VAO: ID of the VAO
    */
    class Model
    {
        const unsigned int VAO;
        const std::vector<unsigned int> VBOs;
    public:
        const unsigned int vertexCount;

        /*
        Model constructor
        VAO: VAO ID
        VBOs: list of VBOs
        vertexCount: number of indices
        */
        Model(unsigned int VAO, std::vector<unsigned int> VBOs, unsigned int vertexCount);

        /*Delete model (VAO and VBOs too)*/
        ~Model();

        /*Bind model*/
        void bind() const;

        /*Render model*/
        void render(bool textured = true) const;
    };

}