/*
 * MeshBuilder.cpp
 *
 * Created by tursh on 1/8/20.
*/

#include <GL/glew.h>
#include <Utils/GLDebug.h>
#include <algorithm>
#include <Utils/Log.h>
#include "Loader/Models/MeshBuilder.h"
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
        positions_.insert(positions_.end(), positions, positions + 3);
        if (texCoords != nullptr)
            texCoords_.insert(texCoords_.end(), texCoords, texCoords + 3);
        if (normals != nullptr)
            normals_.insert(normals_.end(), normals, normals + 3);

        indices_.insert(indices_.end(), TRIANGLE_INDICES, TRIANGLE_INDICES + 3);
        if (invIndices)
            std::reverse(indices_.end() - 3, indices_.end() - 1);

        return positions_.size() - 3;
    }

    void MeshBuilder::AddIndices(const Data<unsigned int> &indices)
    {
        indices_.insert(indices_.end(), indices.data_, indices.data_ + indices.size_);
    }

    unsigned int MeshBuilder::loadVertex(const glm::vec3 &position, const glm::vec2 &texCoord, const glm::vec3 &normal)
    {
        positions_.push_back(position);
        texCoords_.push_back(texCoord);
        normals_.push_back(normal);

        return positions_.size() - 1;
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
        unsigned int startIndex = positions_.size();
        positions_.insert(positions_.end(), (glm::vec3 *) subMeshData.positions.begin(),
                          (glm::vec3 *) subMeshData.positions.end());
        if (subMeshData.textureCoordinates.isValid())
            texCoords_.insert(texCoords_.end(), (glm::vec3 *) subMeshData.textureCoordinates.begin(),
                              (glm::vec3 *) subMeshData.textureCoordinates.end());
        if (subMeshData.normals.isValid())
            normals_.insert(normals_.end(), (glm::vec3 *) subMeshData.normals.begin(),
                            (glm::vec3 *) subMeshData.normals.end());
        indices_.insert(indices_.end(), subMeshData.indices.begin(),
                        subMeshData.indices.end());
        return startIndex;
    }

    void MeshBuilder::translateVertices(unsigned int firstIndex, unsigned int lastIndex, const glm::vec3 &movement)
    {
#ifndef NDEBUG
        if (vertexCount() <= lastIndex)
        logError("You can't translate nonexistent vertices");
#endif
        for (unsigned int i = firstIndex; i <= lastIndex; ++i)
            positions_[i] += movement;
    }

    void MeshBuilder::rotateVertices(unsigned int firstIndex, unsigned int lastIndex, const glm::vec3 &centerOfRotation,
                                     const glm::vec3 &angles)
    {
#ifndef NDEBUG

        if (vertexCount() <= lastIndex)
        logError("You can't translate nonexistent vertices");
#endif
        glm::quat quaternion(angles);

        for (unsigned int i = firstIndex; i <= lastIndex; ++i)
        {
            positions_[i] = quaternion * (positions_[i] - centerOfRotation) + centerOfRotation;
        }
    }

    unsigned int MeshBuilder::vertexCount()
    {
        return positions_.size();
    }


}