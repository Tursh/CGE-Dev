/*
Load data arrays to a Model for rendering
Load OBJ files to a model for rendering
Author: Raphael Tremblay
*/

#pragma once

#include <GL/glew.h>
#include <memory>

namespace CGE::Loader
{

    class Model;

    /*
    Data object used to load data arrays to a VAO
    data: data array
    size: array's size
    */
    template<typename T>
    struct Data
    {
        /**< data array*/
        const T *data_;
        /**< array's size*/
        unsigned int size_;
        /**< data usage*/
        GLenum usage_;

        /*
        Data constructor
        data: data array
        size_: array's size_
        */
        Data(T *data, unsigned int size, GLenum usage = GL_STATIC_DRAW)
                : data_(data), size_(size), usage_(usage) {}

        /*
        Data constructor
        data: data array
        size_: array's size_
        */
        Data(const T *data, unsigned int size, GLenum usage = GL_STATIC_DRAW)
                : data_(data), size_(size), usage_(usage)
        {
        }
    };

/*
        Load data to VAO and return a model that can be rendered
        positions: Data object containing float[] and size_ of array
        texCoords: Data object containing float[] and size_ of array
        indices: Data object containing unsigned int[] and size_ of array
        threeDimension: Is object in 3 dimensions
        */
    std::shared_ptr<Model> DataToVAO(const Data<float> &positions,
                                     const Data<float> &texCoords,
                                     const Data<unsigned int> &indices,
                                     bool threeDimension);

    /*
    Load data to VAO and return a model that can be rendered
    positions: Data object containing float[] and size_ of array
    texCoords: Data object containing float[] and size_ of array
    normals: Data object containing float[] and size_ of array
    indices: Data object containing unsigned int[] and size_ of array
    */
    std::shared_ptr<Model> DataToVAO(const Data<float> &positions,
                                     const Data<float> &texCoords,
                                     const Data<float> &normals,
                                     const Data<unsigned int> &indices);


    /*
    Load data to VAO and return a model that can be rendered (Without texture)
    positions: Data object containing float[] and size_ of array
    indices: Data object containing unsigned int[] and size_ of array
    threeDimension: Is object in 3 dimensions
    */
    std::shared_ptr<Model>
    DataToVAO(const Data<float> &positions, const Data<unsigned int> &indices, bool threeDimension);

    /*
    Load obj file to 3D Model
    filePath: path to the file from the project folder
    */
    std::shared_ptr<Model> loadOBJFile(const char *filePath);

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
     * Load Collada files to 3D Model
     * filePath: path to the file from the project folder
     */
    //std::shared_ptr<AnimatedModel> loadDAEFile(const char *filePath);



    //Load data to VAO when you are not in the render thread
    void DataToVAO(std::shared_ptr<Model> &sharedPtr,
                   Data<float> positions,
                   Data<float> texCoords,
                   Data<unsigned int> indices,
                   bool threeDimension);

    void loadModels();

}