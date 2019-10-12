/*
Load data arrays to a Model for rendering
Author: Raphael Tremblay
*/

#include <GL/glew.h>    //GL*

#include <vector>        //std::vector
#include <Loader/Models/Model.h>
#include <Utils/Log.h>
#include <Loader/Loader.h>
#include <mutex>
#include <condition_variable>
#include <GLFW/glfw3.h>


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
    data: Data object containing unsigned int[] and the size_ of the array
    */
    static void loadIndices(const Data<unsigned int> &data)
    {
        createVBO(GL_ELEMENT_ARRAY_BUFFER);
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size_ * sizeof(unsigned int), data.data_, data.usage_));
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
        GLCall(glBufferData(GL_ARRAY_BUFFER, data.size_ * sizeof(float), data.data_, data.usage_));
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
        GLCall(glBufferData(GL_ARRAY_BUFFER, data.size_ * sizeof(float), data.data_, data.usage_));
        GLCall(glVertexAttribIPointer(index, dataSize, GL_UNSIGNED_INT, 0, nullptr));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    static glm::vec3 getSize(const Data<float> &positions)
    {
        glm::vec3 bigger(0);
        for (int i = 0; i < positions.size_ / 3; ++i)
        {
            if (positions.data_[i * 3] > bigger.x)
                bigger.x = positions.data_[i * 3];
            if (positions.data_[i * 3 + 1] > bigger.y)
                bigger.y = positions.data_[i * 3 + 1];
            if (positions.data_[i * 3 + 2] > bigger.z)
                bigger.z = positions.data_[i * 3 + 2];
        }

        glm::vec3 smaller(0);
        for (int i = 0; i < positions.size_ / 3; ++i)
        {
            if (positions.data_[i * 3] > smaller.x)
                smaller.x = positions.data_[i * 3];
            if (positions.data_[i * 3 + 1] > smaller.y)
                smaller.y = positions.data_[i * 3 + 1];
            if (positions.data_[i * 3 + 2] > smaller.z)
                smaller.z = positions.data_[i * 3 + 2];
        }

        return bigger - smaller;
    }

    /*
    Load data to VAO and return a model that can be rendered
    positions: Data object containing float[] and size_ of array
    texCoords: Data object containing float[] and size_ of array
    indices: Data object containing unsigned int[] and size_ of array
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
        return std::make_shared<Model>(VAO, VBOs, indices.size_, getSize(positions));
    }

    /*
    Load data to VAO and return a model that can be rendered
    positions: Data object containing float[] and size_ of array
    texCoords: Data object containing float[] and size_ of array
    normals: Data object containing float[] and size_ of array
    indices: Data object containing unsigned int[] and size_ of array
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
        return std::make_shared<Model>(VAO, VBOs, indices.size_, getSize(positions));
    }


    /*
    Load data to VAO and return a model that can be rendered (without texture)
    positions: Data object containing float[] and size_ of array
    indices: Data object containing unsigned int[] and size_ of array
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
        return std::make_shared<Model>(VAO, VBOs, indices.size_, getSize(positions));
    }

    std::vector<std::tuple<std::shared_ptr<Model> &, const Data<float>, const Data<float>, const Data<unsigned int>, bool>> modelsExtraBuffer;
    std::vector<std::tuple<std::shared_ptr<Model> &, const Data<float>, const Data<float>, const Data<unsigned int>, bool>> modelsToLoad;
    bool loadingModel = false;

    void DataToVAO(std::shared_ptr<Model> &sharedPtr,
                   Data<float> positions,
                   Data<float> texCoords,
                   Data<unsigned int> indices,
                   bool threeDimension)
    {
        //Copy vertices
        float *positionData = new float[positions.size_];
        std::copy(positions.data_, positions.data_ + positions.size_, positionData);

        float *texCoordsData = new float[texCoords.size_];
        std::copy(texCoords.data_, texCoords.data_ + texCoords.size_, texCoordsData);

        unsigned int *indicesData = new unsigned int[indices.size_];
        std::copy(indices.data_, indices.data_ + indices.size_, indicesData);

        modelsExtraBuffer.emplace_back(
                sharedPtr,
                Data<float>(positionData, positions.size_, positions.usage_),
                Data<float>(texCoordsData, texCoords.size_, texCoords.usage_),
                Data<unsigned int>(indicesData, indices.size_, indices.usage_),
                threeDimension);
    }

    int loadingIndex = 0;

    void loadModels()
    {
        if(modelsToLoad.empty())
        {
            modelsToLoad.swap(modelsExtraBuffer);
            return;
        }

        loadingModel = true;
        bool loadedAllModels = loadingIndex + 200 > modelsToLoad.size();
        int maxLoadingIndex = loadedAllModels ? (int)modelsToLoad.size() : 200 + loadingIndex;
        for (; loadingIndex < maxLoadingIndex; ++loadingIndex)
        {
            auto &model = modelsToLoad[loadingIndex];
            auto &modelPtr = std::get<0>(model);
            const auto &positions = std::get<1>(model);
            const auto &texCoords = std::get<2>(model);
            const auto &indices = std::get<3>(model);

            modelPtr = DataToVAO(positions, texCoords, indices, std::get<4>(model));

            delete[] positions.data_;
            delete[] texCoords.data_;
            delete[] indices.data_;
        }
        if(loadedAllModels)
        {
            loadingIndex = 0;
            modelsToLoad.clear();
            modelsToLoad.swap(modelsExtraBuffer);
        }
        loadingModel = false;
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
    //    return std::make_shared<AnimatedModel>(VAO, VBOs, indices.size_);
    //}

}
