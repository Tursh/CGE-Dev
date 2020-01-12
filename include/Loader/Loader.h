/*
Load data arrays to a Mesh for rendering
Load OBJ files to a model for rendering
Author: Raphael Tremblay
*/

#pragma once

#include <GL/glew.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace CGE::Loader
{

    class Mesh;

    /**
     * Data wrapper used to load data arrays to a VAO
     * @tparam T Data type
     */
    template<typename T>
    struct Data
    {
        /**< data array*/
        const T *data_{};
        /**< array's size*/
        unsigned int size_;
        /**< data usage*/
        GLenum usage_;

        /*
        Data constructor
        data: data array
        size_: array's size_
        */
        //Data(T *data, unsigned int size, bool makeCopy = false, GLenum usage = GL_STATIC_DRAW)
        //        : data_(data), size_(size), usage_(usage) {}

        /**
         * Create a data wrapper
         * @param data Data array
         * @param size Array's size
         * @param makeCopy Make a copy of the array (default: false)
         * @param usage Expected usage pattern of the data store (default: GL_STATIC_DRAW)
         */
        Data(T const *data, unsigned int size, GLenum usage = GL_STATIC_DRAW)
                : data_(data), size_(size), usage_(usage)
        {
            //if (makeCopy)
            //{
            //    data_ = new T[size];
            //    std::copy(data, data + size, data_);
            //}
        }

        Data() = default;

        /**
         * Create a data wrapper ** WARNING: You will need to delete the data array yourself **
         * @param data Data vector
         * @param makeCopy Make a copy of the array (default: true)
         * @param usage Expected usage pattern of the data store (default: GL_STATIC_DRAW)
         */
        explicit Data(const std::vector<glm::vec3> &data, bool makeCopy = true, GLenum usage = GL_STATIC_DRAW);

        /**
         * Create a data wrapper ** WARNING: You will need to delete the data array yourself **
         * @param data Data vector
         * @param makeCopy Make a copy of the array (default: true)
         * @param usage Expected usage pattern of the data store (default: GL_STATIC_DRAW)
         */
        explicit Data(const std::vector<glm::vec2> &data, bool makeCopy = true, GLenum usage = GL_STATIC_DRAW);

        /**
         * Create a data wrapper ** WARNING: You will need to delete the data array yourself **
         * @param data Data vector
         * @param makeCopy Make a copy of the array (default: true)
         * @param usage Expected usage pattern of the data store (default: GL_STATIC_DRAW)
         */
        explicit Data(const std::vector<T> &data, bool makeCopy = true, GLenum usage = GL_STATIC_DRAW);

        /**
         * Delete all stored data
         */
        void deleteData();

        /**
         * Is data valid
         * @return If there is data stored in the wrapper
         */
        bool isValid() const;
    };

    typedef std::shared_ptr<Mesh> SharedMesh;

    struct MeshData
    {
        Data<unsigned int> indices;
        Data<float> positions;
        Data<float> textureCoordinates;
        Data<float> normals;
        bool threeDimension = true;

        /**
         * Check if the mesh is valid to be loaded
         */
        bool isValid() const;

        /**
         * Delete all data
         */
        void destroy();

        SharedMesh load();
    };

/**
 * Load data to VAO and return a model that can be rendered
 * @param positionsData object containing float[] and size_ of array
 * @param texCoordsData object containing float[] and size_ of array
 * @param indices Data object containing unsigned int[] and size_ of array
 * @param threeDimension Is object in 3 dimensions
 * @return 3D mesh
 */
    SharedMesh DataToVAO(const Data<float> &positions,
                         const Data<float> &texCoords,
                         const Data<unsigned int> &indices,
                         bool threeDimension);

/**
 * Load data to VAO and return a model that can be rendered
 * @param positions Data object containing float[] and size_ of array
 * @param texCoords Data object containing float[] and size_ of array
 * @param normals Data object containing float[] and size_ of array
 * @param indices Data object containing unsigned int[] and size_ of array
 * @return 3D mesh
 */
    SharedMesh DataToVAO(const Data<float> &positions,
                         const Data<float> &texCoords,
                         const Data<float> &normals,
                         const Data<unsigned int> &indices);

/**
 * Load data to VAO and return a model that can be rendered (Without texture)
 * @param positions Data object containing float[] and size_ of array
 * @param indices Data object containing unsigned int[] and size_ of array
 * @param threeDimension Is object in 3 dimensions
 * @return 3D mesh without texture coordinates
 */
    SharedMesh DataToVAO(const Data<float> &positions, const Data<unsigned int> &indices, bool threeDimension);

    SharedMesh DataToVAO(const MeshData &meshData);

/**
 * Load obj file to 3D Mesh
 * @param filePath Path to the file from the project folder
 * @return 3D mesh
 */
    SharedMesh loadOBJFile(const char *filePath);

/*
 * Load Animated model to VAO
 */
//std::shared_ptr<AnimatedModel> DataToVAO(const Data<float> &positions,
//                                         const Data<float> &texCoords,
//                                         const Data<float> &normals,
//                                         const Data<unsigned int> &indices,
//                                         const Data<unsigned int> &jointIDs,
//                                         const Data<float> &weight);

/*
 * Load Collada files to 3D Mesh
 * filePath: path to the file from the project folder
 */
//std::shared_ptr<AnimatedModel> loadDAEFile(const char *filePath);



/**
 * Load data to mesh on next rendering (If not on rendering thread)
 * @param sharedPtr Pointer where to load the mesh
 * @param meshData Data of the mesh to load
 */
    void DataToVAO(SharedMesh &sharedPtr, MeshData meshData);

/**
 * Load buffered meshes (when on rendering thread)
 * This is function is called during the window update
 */
    void loadMeshes();

}