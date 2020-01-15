/*
 * MeshBuilder.h
 *
 * Created by tursh on 1/8/20.
*/

#pragma once


#include <Loader/Models/Mesh.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace CGE::Loader
{

    class MeshBuilder
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
        loadTriangle(const glm::vec3 *positions, const glm::vec2 *texCoords, const glm::vec3 *normals,
                     bool invIndices = false);

        /**
         * Use existing vertices to create triangle
         * @param indices List of vertex to use as indices
         */
        void AddIndices(const Data<unsigned int> &indices);

        /**
         * Load vertex to model without using it
         * @param position Vertex position
         * @param texCoord Vertex texture coordinate
         * @param normal Vertex normal
         * @return Vertex index
         */
        unsigned int loadVertex(const glm::vec3 &position, const glm::vec2 &texCoord, const glm::vec3 &normal);

        /**
         * Add an existing mesh to the current mesh
         * @param subMeshData The existing mesh data
         * @return The start index of the added mesh in the current mesh
         */
        unsigned int loadSubMesh(const MeshData &subMeshData);

        /**
         * Translate a range of vertices
         * @param firstIndex The index of the first vertex
         * @param lastIndex The index of the last vertex
         * @param movement The movement vector
         */
        void translateVertices(unsigned int firstIndex, unsigned int lastIndex, const glm::vec3 &movement);

        /**
         * Rotate a range of vertices
         * @param firstIndex The index of the first vertex
         * @param lastIndex The index of the last vertex
         * @param centerOfRotation The position to rotate around
         * @param angles The xyz angle in degree
         */
        void rotateVertices(unsigned int firstIndex, unsigned int lastIndex, const glm::vec3 &centerOfRotation,
                            const glm::vec3 &angles);

        /**
         * Get the number of vertex in the mesh
         * @return positions_.size()
         */
        unsigned int vertexCount();

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
