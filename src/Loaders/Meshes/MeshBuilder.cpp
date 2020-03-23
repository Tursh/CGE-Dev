/*
 * MeshBuilder.cpp
 *
 * Created by tursh on 1/8/20.
*/

#include <GL/glew.h>
#include <Utils/GLDebug.h>
#include <algorithm>
#include <Utils/Log.h>
#include "Loader/Meshes/MeshBuilder.h"
#include <Loader/Loader.h>
#include <glm/gtc/quaternion.hpp>

namespace CGE::Loader
{
    const unsigned int TRIANGLE_INDICES[] =
            {
                    0, 1, 2, 2, 1, 3
            };

    unsigned int
    MeshBuilder::loadTriangle(const glm::vec3 *positions, const glm::vec2 *texCoords, const glm::vec3 *normals,
                              bool invIndices)
    {
        unsigned int firstVertex = vertexCount();
        positions_.insert(positions_.end(), positions, positions + 3);
        if (texCoords != nullptr)
            texCoords_.insert(texCoords_.end(), texCoords, texCoords + 3);
        if (normals != nullptr)
            normals_.insert(normals_.end(), normals, normals + 3);

        unsigned int firstIndex = loadIndices({TRIANGLE_INDICES, 3});
        incrementIndices(firstIndex, firstIndex + 3, firstVertex);
        if (invIndices)
            std::reverse(indices_.end() - 3, indices_.end() - 1);

        return firstVertex;
    }

    unsigned int MeshBuilder::loadIndices(const Data<unsigned int> &indices, bool invIndices)
    {
        unsigned int firstIndexPosition = indexCount();

        auto firstIt = indices_.end();
        indices_.insert(firstIt, indices.first(), indices.last());

        if (invIndices)
            std::reverse(firstIt, indices_.end() - 1);

        return firstIndexPosition;
    }

    unsigned int MeshBuilder::loadVertex(const glm::vec3 &position, const glm::vec2 &texCoord, const glm::vec3 &normal)
    {
        positions_.push_back(position);
        if (texCoord != glm::vec2(INT_MAX))
            texCoords_.push_back(texCoord);
        if (normal != glm::vec3(INT_MAX))
            normals_.push_back(normal);

        return vertexCount() - 1;
    }

    template<>
    Data<unsigned int>::Data(const std::vector<unsigned int> &data, bool makeCopy, GLenum usage);

    MeshData MeshBuilder::toMeshData()
    {
        MeshData meshData;
        meshData.positions = Data<float>(positions_);
        meshData.textureCoordinates = Data<float>(texCoords_);
        meshData.normals = Data<float>(normals_);
        meshData.indices = Data<unsigned int>(indices_);

        return meshData;
    }

    SharedMesh MeshBuilder::toSharedMesh()
    {
        MeshData data = toMeshData();

#ifndef NDEBUG
        if (isOnOpenGLThread())
            return DataToVAO(data);
        else
        logError("You can't load a mesh outside the render thread");
        return nullptr;
#else
        return DataToVAO(data);
#endif
    }

    void MeshBuilder::reset()
    {
        positions_.clear();
        texCoords_.clear();
        normals_.clear();
        indices_.clear();
    }

    void MeshBuilder::loadToSharedMesh(SharedMesh &sharedMesh)
    {
        DataToVAO(sharedMesh, toMeshData());
    }

    unsigned int MeshBuilder::loadSubMesh(const MeshData &subMeshData)
    {
        unsigned int startVertex = vertexCount();

#ifndef NDEBUG
        if (!subMeshData.isValid())
        logError("You tried to load an invalid mesh!");
#endif

        positions_.insert(positions_.end(), (glm::vec3 *) subMeshData.positions.first(),
                          (glm::vec3 *) subMeshData.positions.last());

        if (subMeshData.textureCoordinates.isValid())
            texCoords_.insert(texCoords_.end(), (glm::vec3 *) subMeshData.textureCoordinates.first(),
                              (glm::vec3 *) subMeshData.textureCoordinates.last());

        if (subMeshData.normals.isValid())
            normals_.insert(normals_.end(), (glm::vec3 *) subMeshData.normals.first(),
                            (glm::vec3 *) subMeshData.normals.last());

        indices_.insert(indices_.end(), subMeshData.indices.first(),
                        subMeshData.indices.last());

        return startVertex;
    }

    void MeshBuilder::translateVertices(const glm::vec3 &movement, unsigned int firstVertex, unsigned int lastVertex)
    {
        if (lastVertex == UINT_MAX)
            lastVertex = vertexCount();
#ifndef NDEBUG
        else if (vertexCount() < lastVertex)
        logError("You can't translate nonexistent vertices -> lastVertex: " << lastVertex << " vertexCount: "
                                                                            << vertexCount());
#endif
        for (unsigned int i = firstVertex; i < lastVertex; ++i)
            positions_[i] += movement;
    }

    void
    MeshBuilder::rotateVertices(const glm::vec3 &centerOfRotation, const glm::vec3 &angles, unsigned int firstVertex,
                                unsigned int lastVertex)
    {
        if (lastVertex == UINT_MAX)
            lastVertex = vertexCount();
#ifndef NDEBUG
        else if (vertexCount() < lastVertex)
        logError("You can't rotate nonexistent vertices -> lastVertex: " << lastVertex << " vertexCount: "
                                                                         << vertexCount());
#endif
        glm::quat quaternion(angles);

        for (; firstVertex < lastVertex; ++firstVertex)
        {
            positions_[firstVertex] = quaternion * (positions_[firstVertex] - centerOfRotation) + centerOfRotation;
        }
    }

    glm::vec2 unused2Vector(INT_MAX);
    glm::vec3 unused3Vector(INT_MAX);

    void MeshBuilder::transformVertices(
            std::function<void(glm::vec3 &position, glm::vec2 &texCoords, glm::vec3 &normal)> transformation,
            unsigned int firstVertex, unsigned int lastVertex)
    {
        if (lastVertex == UINT_MAX)
            lastVertex = vertexCount();
#ifndef NDEBUG
        else if (vertexCount() < lastVertex)
        logError("You can't rotate nonexistent vertices -> lastVertex: " << lastVertex << " vertexCount: "
                                                                         << vertexCount());
#endif
        for (; firstVertex < lastVertex; ++firstVertex)
            transformation(positions_[firstVertex], texCoords_.empty() ? unused2Vector : texCoords_[firstVertex],
                           normals_.empty() ? unused3Vector : normals_[firstVertex]);

#ifndef NDEBUG
        if (unused2Vector != glm::vec2(INT_MAX) && unused3Vector != glm::vec3(INT_MAX))
        logError(
                "The given transformation function has used unexisting data -"
                " Please check documentation for more details");
#endif
    }

    unsigned int MeshBuilder::vertexCount()
    {
        return positions_.size();
    }

    bool MeshBuilder::isValid() const
    {
        return !positions_.empty() && !indices_.empty()     //Is the positions and indices
               && (texCoords_.empty() ||
                   texCoords_.size() == positions_.size())  //If there is texCoords, it there as many as positions
               && (normals_.empty() ||
                   normals_.size() == positions_.size());   //If there is normals, is there as many as positions
    }

    unsigned int MeshBuilder::indexCount()
    {
        return indices_.size();
    }

    void MeshBuilder::incrementIndices(unsigned int scalarToIncrement, unsigned int firstIndex, unsigned int lastIndex)
    {
        if (lastIndex == UINT_MAX)
            lastIndex = indexCount();
#ifndef NDEBUG
        else if (lastIndex > indexCount())
        logError("You can't increment nonexistent indices -> lastIndex: " << lastIndex << " indexCount: "
                                                                          << indexCount());
#endif

        for (; firstIndex < lastIndex; ++firstIndex)
            indices_[firstIndex] += scalarToIncrement;
    }


    void MeshBuilder::invertIndices(unsigned int firstIndex, unsigned int lastIndex)
    {
        if (lastIndex == UINT_MAX)
            lastIndex = indexCount();
#ifndef NDEBUG
        else if (lastIndex > indexCount())
        logError("You can't invert nonexistent indices -> lastIndex: " << lastIndex << " indexCount: "
                                                                          << indexCount());
#endif
        std::reverse(indices_.begin() + firstIndex, indices_.begin() + lastIndex);
    }

    unsigned int
    MeshBuilder::loadVertices(const glm::vec3 *vertices, const glm::vec2 *texCoords, const glm::vec3 *normals,
                              unsigned int vertexCount)
    {
        unsigned int startVertex = this->vertexCount();

        positions_.insert(positions_.end(), vertices, vertices + vertexCount);

        if (texCoords != nullptr)
            texCoords_.insert(texCoords_.end(), texCoords, texCoords + vertexCount);

        if (normals != nullptr)
            normals_.insert(normals_.end(), normals, normals + vertexCount);

        return startVertex;
    }

}