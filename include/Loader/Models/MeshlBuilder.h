/*
 * MeshlBuilder.h
 *
 * Created by tursh on 1/8/20.
*/

#pragma once


#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <Loader/Loader.h>

namespace CGE::Loader
{

    class MeshlBuilder
    {
        std::vector<glm::vec3> positions_;
        std::vector<glm::vec2> texCoords_;
        std::vector<glm::vec3> normals_;
        std::vector<unsigned int> indices_;

    public:
        /**
         * Add a triangle to the mesh
         * @param positions The 3 vertex positions
         * @param texCoords The corresponding texture coordinates
         * @param normals The corresponding normals
         * @param invIndices Reverse the triangle indices
         * @return The triangle index
         */
        unsigned int
        loadTriangle(glm::vec3 *positions, glm::vec2 *texCoords, glm::vec3 *normals, bool invIndices = false);

        void AddIndices(Data<unsigned int> indices);

        /**
         * Load vertex to model without using it
         * @param position Vertex position
         * @param texCoord Vertex texture coordinate
         * @param normal Vertex normal
         * @return Vertex index
         */
        unsigned int loadVertex(glm::vec3 position, glm::vec2 texCoord, glm::vec3 normal);

        /**
         * Load position, texcoords, normals and indices to a MeshData object
         * @return MeshData to be loaded
         */
        MeshData toMeshData();

        /**
         * Load the mesh to VAO
         * @return SharedMesh to be rendered
         */
        SharedMesh toSharedMesh();

        /**
         * Load the mesh to the given shared mesh ** To load outside of render thread **
         * @param sharedMesh The shared mesh to load to
         */
        void loadToSharedMesh(SharedMesh &sharedMesh);

        /**
         * Reset built mesh
         */
        void reset();
    };

}
