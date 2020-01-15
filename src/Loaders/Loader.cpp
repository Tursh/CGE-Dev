/*
Load data arrays to a Mesh for rendering
Author: Raphael Tremblay
*/

#include <GL/glew.h>    //GL*

#include <vector>        //std::vector
#include <Loader/Models/Mesh.h>
#include <Utils/Log.h>
#include <Loader/Loader.h>
#include <mutex>
#include <condition_variable>
#include <GLFW/glfw3.h>
#include <thread>


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
    SharedMesh
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
        return std::make_shared<Mesh>(VAO, VBOs, indices.size_, getSize(positions));
    }

    /*
    Load data to VAO and return a model that can be rendered
    positions: Data object containing float[] and size_ of array
    texCoords: Data object containing float[] and size_ of array
    normals: Data object containing float[] and size_ of array
    indices: Data object containing unsigned int[] and size_ of array
    */
    SharedMesh
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
        return std::make_shared<Mesh>(VAO, VBOs, indices.size_, getSize(positions));
    }


    /*
    Load data to VAO and return a model that can be rendered (without texture)
    positions: Data object containing float[] and size_ of array
    indices: Data object containing unsigned int[] and size_ of array
    */
    SharedMesh
    DataToVAO(const Data<float> &positions, const Data<unsigned int> &indices, bool threeDimension)
    {
        const int VAO = createVAO();
        loadDataInAttribArray(0, threeDimension ? 3 : 2, positions);
        loadIndices(indices);
        GLCall(glBindVertexArray(0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        const std::vector<unsigned int> VBOs = buffers;
        buffers.clear();
        return std::make_shared<Mesh>(VAO, VBOs, indices.size_, getSize(positions));
    }

    SharedMesh Loader::DataToVAO(const MeshData &meshData)
    {
#ifndef NDEBUG
        if (!isOnOpenGLThread())
        logError("There is no openGL context in this thread!");

        if (!meshData.isValid())
        logError("This mesh is invalid!");
#endif

        unsigned int VAO = createVAO();

        loadDataInAttribArray(0, meshData.threeDimension ? 3 : 2, meshData.positions);

        if (meshData.textureCoordinates.size_ != 0)
            loadDataInAttribArray(1, 2, meshData.textureCoordinates);

        if (meshData.normals.size_ != 0)
            loadDataInAttribArray(2, 3, meshData.normals);

        loadIndices(meshData.indices);

        GLCall(glBindVertexArray(0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        const std::vector<unsigned int> VBOs = buffers;
        buffers.clear();

        return std::make_shared<Mesh>(VAO, VBOs, meshData.indices.size_, getSize(meshData.positions));
    }

    std::vector<std::tuple<SharedMesh &, MeshData>> modelsExtraBuffer;
    std::vector<std::tuple<SharedMesh &, MeshData>> modelsToLoad;
    bool loadingModel = false;

    void Loader::DataToVAO(SharedMesh &sharedPtr, MeshData meshData)
    {
        //Copy vertices to loader memory
        float *positionData = new float[meshData.positions.size_];
        std::copy(meshData.positions.data_, meshData.positions.data_ + meshData.positions.size_, positionData);
        meshData.positions.data_ = positionData;

        float *texCoordsData = new float[meshData.textureCoordinates.size_];
        std::copy(meshData.textureCoordinates.data_,
                  meshData.textureCoordinates.data_ + meshData.textureCoordinates.size_, texCoordsData);
        meshData.textureCoordinates.data_ = texCoordsData;

        unsigned int *indicesData = new unsigned int[meshData.indices.size_];
        std::copy(meshData.indices.data_, meshData.indices.data_ + meshData.indices.size_, indicesData);
        meshData.indices.data_ = indicesData;

        std::tuple<SharedMesh &, MeshData> meshWithPointer = {sharedPtr, meshData};

        while (loadingModel)
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

        modelsExtraBuffer.push_back(meshWithPointer);
    }

    void loadMeshes()
    {
        unsigned int size = modelsToLoad.size();
        if (size == 0)
        {
            loadingModel = true;
            modelsToLoad.swap(modelsExtraBuffer);
            loadingModel = false;
            return;
        }

        for (auto &model : modelsToLoad)
        {
            auto &meshPtr = std::get<0>(model);
            auto &meshData = std::get<1>(model);

            meshPtr = DataToVAO(meshData);

            meshData.destroy();
        }
        modelsToLoad.clear();
        loadingModel = true;
        modelsToLoad.swap(modelsExtraBuffer);
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

    //template<typename T>
    //Data<T>::Data(const T *data, unsigned int size, bool makeCopy, GLenum usage)

    template<>
    Data<float>::Data(const std::vector<glm::vec3> &data, bool makeCopy, GLenum usage)
            : data_((float *) data.data()), size_(3 * data.size()), usage_(usage)
    {
        if (makeCopy)
        {
            data_ = new float[3 * data.size()];
            std::copy((float *) data.data(), (float *) data.data() + size_, (float *) data_);
        }
    }

    template<>
    Data<float>::Data(const std::vector<glm::vec2> &data, bool makeCopy, GLenum usage)
            : data_((float *) data.data()), size_(2 * data.size()), usage_(usage)
    {
        if (makeCopy)
        {
            data_ = new float[2 * data.size()];
            std::copy((float *) data.data(), (float *) data.data() + size_, (float *) data_);
        }
    }

    template<typename T>
    Data<T>::Data(const std::vector<T> &data, bool makeCopy, GLenum usage)
            : data_(data.data()), size_(data.size()), usage_(usage)
    {
        if (makeCopy)
        {
            data_ = new T[data.size()];
            std::copy((T *) data.data(), (T *) data.data() + data.size(), (T *) data_);
        }
    }

    template<typename T>
    void Data<T>::deleteData()
    {
        if (isValid())
        {
            delete[] data_;
            size_ = 0;
        }
    }

    template<typename T>
    bool Data<T>::isValid() const
    {
        return size_ != 0;
    }

    template<typename T>
    const T *Data<T>::begin() const
    {
        return data_;
    }

    template<typename T>
    const T *Data<T>::end() const
    {
        return data_ + size_;
    }

    bool MeshData::isValid() const
    {
        return positions.isValid() && indices.isValid();
    }

    void MeshData::destroy()
    {
        positions.deleteData();
        textureCoordinates.deleteData();
        normals.deleteData();
        indices.deleteData();
    }

    SharedMesh MeshData::load()
    {
        if (isOnOpenGLThread())
            return DataToVAO(*this);
        else
        logError("You can't load a model outside the render thread");
        return nullptr;
    }

    template
    class Data<unsigned int>;
    template
    class Data<float>;
}
