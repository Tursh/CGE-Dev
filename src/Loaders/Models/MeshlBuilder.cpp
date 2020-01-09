/*
 * MeshlBuilder.cpp
 *
 * Created by tursh on 1/8/20.
*/

#include <GL/glew.h>
#include <Utils/GLDebug.h>
#include <algorithm>
#include <Utils/Log.h>
#include "Loader/Models/MeshlBuilder.h"

namespace CGE::Loader
{
    const unsigned int TRIANGLE_INDICES[] =
            {
                    0, 1, 2, 2, 1, 3
            };

    unsigned int
    MeshlBuilder::loadTriangle(glm::vec3 *positions, glm::vec2 *texCoords, glm::vec3 *normals, bool invIndices)
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

    void MeshlBuilder::AddIndices(Data<unsigned int> indices)
    {
        indices_.insert(indices_.end(), indices.data_, indices.data_ + indices.size_);
    }

    unsigned int MeshlBuilder::loadVertex(glm::vec3 position, glm::vec2 texCoord, glm::vec3 normal)
    {
        positions_.push_back(position);
        texCoords_.push_back(texCoord);
        normals_.push_back(normal);

        return positions_.size() - 1;
    }

    MeshData MeshlBuilder::toMeshData()
    {
        MeshData meshData;
        meshData.positions = Data<float>(positions_);
        meshData.textureCoordinates = Data<float>(texCoords_);
        meshData.normals = Data<float>(normals_);
        meshData.indices = Data<unsigned int>(indices_);

        return meshData;
    }

    SharedMesh MeshlBuilder::toSharedMesh()
    {
        MeshData data = toMeshData();

        if (isOnOpenGLThread())
            return DataToVAO(data);
        else
        logError("You can't load a mesh outside the render thread");
        return nullptr;
    }

    void MeshlBuilder::reset()
    {
        positions_.clear();
        texCoords_.clear();
        normals_.clear();
        indices_.clear();
    }

    void MeshlBuilder::loadToSharedMesh(SharedMesh &sharedMesh)
    {
        DataToVAO(sharedMesh, toMeshData());
    }
}