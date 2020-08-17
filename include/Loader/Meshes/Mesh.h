#pragma once

#include <vector>
#include <Loader/Loader.h>
#include <glm/glm.hpp>

namespace CGE::Loader
{
    /**
     * @brief Basic Mesh containing a 2D or 3D model ready to be rendered
     */
    class Mesh
    {
        const unsigned int VAO;
        const std::vector<unsigned int> VBOs;
    public:
        const unsigned int vertexCount;
        const glm::vec3 size;

        /**
         * Mesh constructor
         * @param VAO VAO ID
         * @param VBOs list of VBOs
         * @param vertexCount  number of indices
         * @param size 3D size
         */
        Mesh(unsigned int VAO, std::vector<unsigned int> VBOs, unsigned int vertexCount, glm::vec3 size);

        /**
         * Delete model (VAO and VBOs too)
         */
        ~Mesh();

        /**
         * Bind model to render
         */
        void bind() const;

        /**
         * Render model
         * @param textured Is the mesh textured
         */
        void render(bool textured = true) const;

        void setTexCoords(unsigned int offset, const Data<float> &data);
    };


}