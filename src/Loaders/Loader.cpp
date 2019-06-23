/*
Load data arrays to a Model for rendering
Author: Raphael Tremblay
*/

#include <GL/glew.h>    //GL*

#include <vector>        //std::vector
#include <Loader/Models/Model.h>
#include <Utils/Log.h>
#include <Loader/Loader.h>


#include "Utils/GLDebug.h"    //GLCall

namespace CGE::Loader
{

    /*Create a temporary buffer list for VBOs*/
    static std::vector<unsigned int> buffers;

    /*Create and bind a VAO*/
    static unsigned int createVAO()
    {
        unsigned int VAO;
        GLCall(glGenVertexArrays(1, &VAO));
        GLCall(glBindVertexArray(VAO));
        return VAO;
    }

    /*
    Create and bind a VBO
    Type: type of VBO (GL_ARRAY_BUFFER -> data, GL_ELEMENT_ARRAY_BUFFER -> indices)
    */
    static unsigned int createVBO(GLenum type)
    {
        unsigned int VBO;
        GLCall(glGenBuffers(1, &VBO));
        buffers.push_back(VBO);
        GLCall(glBindBuffer(type, VBO));
        return VBO;
    }

    /*
    Load indices to VAO
    data: Data object containing unsigned int[] and the size of the array
    */
    static void loadIndices(const Data<unsigned int> &data)
    {
        createVBO(GL_ELEMENT_ARRAY_BUFFER);
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size * sizeof(unsigned int), data.data, data.usage));
    }

    /**
     * Load floats to VAO
     * @param index index pointer (pos -> 0, texCoords -> 1, norm -> 2)
     * @param dataSize size that take one part of data (pos -> 3, tex -> 2, norm -> 3)
     * @param data Data object containing float[] and the size of the array
     */
    static void
    loadDataInAttribArray(const unsigned int &index, const unsigned int &dataSize, const Data<float> &data)
    {
        createVBO(GL_ARRAY_BUFFER);
        GLCall(glBufferData(GL_ARRAY_BUFFER, data.size * sizeof(float), data.data, data.usage));
        GLCall(glVertexAttribPointer(index, dataSize, GL_FLOAT, false, 0, nullptr));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    /**
     * Load unsigned integers to VAO
     * @param index index pointer (pos -> 0, texCoords -> 1, norm -> 2)
     * @param dataSize size that take one part of data (pos -> 3, tex -> 2, norm -> 3)
     * @param data Data object containing float[] and the size of the array
     */
    static void
    loadDataInAttribArray(const unsigned int &index, const unsigned int &dataSize, const Data<unsigned int> &data)
    {
        createVBO(GL_ARRAY_BUFFER);
        GLCall(glBufferData(GL_ARRAY_BUFFER, data.size * sizeof(float), data.data, data.usage));
        GLCall(glVertexAttribIPointer(index, dataSize, GL_UNSIGNED_INT, 0, nullptr));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    static glm::vec3 getSize(const Data<float> &positions)
    {
        glm::vec3 size(0);
        for(int i = 0; i < positions.size; ++i)
        {
            if(positions.data[i * 3] > size.x)
                size.x = positions.data[i];
            if(positions.data[i * 3 + 1] > size.y)
                size.x = positions.data[i];
            if(positions.data[i * 3 + 2] > size.z)
                size.x = positions.data[i];
        }
        return size;
    }

    /*
    Load data to VAO and return a model that can be rendered
    positions: Data object containing float[] and size of array
    texCoords: Data object containing float[] and size of array
    indices: Data object containing unsigned int[] and size of array
    threeDimension: Is object in 3 dimensions
    */
    std::shared_ptr<Model>
    DataToVAO(const Data<float> &positions, const Data<float> &texCoords, const Data<unsigned int> &indices,
              bool threeDimension)
    {
        const int VAO = createVAO();
        loadDataInAttribArray(0, threeDimension ? 3 : 2, positions);
        loadDataInAttribArray(1, 2, texCoords);
        loadIndices(indices);
        GLCall(glBindVertexArray(0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        const std::vector<unsigned int> VBOs = buffers;
        buffers.clear();
        return std::make_shared<Model>(VAO, VBOs, indices.size, getSize(positions));
    }

    /*
    Load data to VAO and return a model that can be rendered
    positions: Data object containing float[] and size of array
    texCoords: Data object containing float[] and size of array
    normals: Data object containing float[] and size of array
    indices: Data object containing unsigned int[] and size of array
    */
    std::shared_ptr<Model>
    DataToVAO(const Data<float> &positions, const Data<float> &texCoords, const Data<float> &normals,
              const Data<unsigned int> &indices)
    {
        const int VAO = createVAO();
        loadDataInAttribArray(0, 3, positions);
        loadDataInAttribArray(1, 2, texCoords);
        loadDataInAttribArray(2, 3, normals);
        loadIndices(indices);
        GLCall(glBindVertexArray(0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        const std::vector<unsigned int> VBOs = buffers;
        buffers.clear();
        return std::make_shared<Model>(VAO, VBOs, indices.size, getSize(positions));
    }


    /*
    Load data to VAO and return a model that can be rendered (without texture)
    positions: Data object containing float[] and size of array
    indices: Data object containing unsigned int[] and size of array
    */
    std::shared_ptr<Model>
    DataToVAO(const Data<float> &positions, const Data<unsigned int> &indices, bool threeDimension)
    {
        const int VAO = createVAO();
        loadDataInAttribArray(0, threeDimension ? 3 : 2, positions);
        loadIndices(indices);
        GLCall(glBindVertexArray(0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        const std::vector<unsigned int> VBOs = buffers;
        buffers.clear();
        return std::make_shared<Model>(VAO, VBOs, indices.size, getSize(positions));
    }

    std::vector<std::tuple<std::shared_ptr<Model> *, const Data<float>, const Data<float>, const Data<unsigned int>, bool>> modelsToLoad;

    void DataToVAO(std::shared_ptr<Model> *sharedPtr,
                   Data<float> positions,
                   Data<float> texCoords,
                   Data<unsigned int> indices,
                   bool threeDimension)
    {
        //Copy vertices
        auto *positionArray = new float[positions.size];
        std::copy(positions.data, positions.data + positions.size, positionArray);
        positions.data = positionArray;

        auto *texCoordsArray = new float[texCoords.size];
        std::copy(texCoords.data, texCoords.data + texCoords.size, texCoordsArray);
        texCoords.data = texCoordsArray;

        auto *indicesArray = new unsigned int[indices.size];
        std::copy(indices.data, indices.data + indices.size, indicesArray);
        indices.data = indicesArray;

        modelsToLoad.push_back(std::make_tuple(
                sharedPtr,
                positions,
                texCoords,
                indices,
                threeDimension));
    }

    void loadModels()
    {
        for (auto vertices : modelsToLoad)
        {
            *std::get<0>(vertices) = DataToVAO(std::get<1>(vertices), std::get<2>(vertices), std::get<3>(vertices),
                                               std::get<4>(vertices));
        }
        modelsToLoad.clear();
    }

    //std::shared_ptr<AnimatedModel>
    //Loader::DataToVAO(const Data<float> &positions, const Data<float> &texCoords, const Data<float> &normals,
    //                  const Data<unsigned int> &indices, const Data<unsigned int> &jointIDs,
    //                  const Data<float> &weights)
    //{
    //    const int VAO = createVAO();
    //    loadDataInAttribArray(0, 3, positions);
    //    loadDataInAttribArray(1, 2, texCoords);
    //    loadDataInAttribArray(2, 3, normals);
    //    loadIndices(indices);
    //    loadDataInAttribArray(3, 3, jointIDs);
    //    loadDataInAttribArray(4, 3, weights);
    //    GLCall(glBindVertexArray(0));
    //    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    //    const std::vector<unsigned int> VBOs = buffers;
    //    buffers.clear();
    //    return std::make_shared<AnimatedModel>(VAO, VBOs, indices.size);
    //}

}
