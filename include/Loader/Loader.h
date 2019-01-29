/*
Load data arrays to a Model for rendering
Load OBJ files to a model for rendering
Author: Raphael Tremblay
*/

#pragma once

#include <memory>
#include "Loader/Models/Model.h"    //Model

namespace CGE
{
    namespace Loader
    {

        /*
        Data object used to load data arrays to a VAO
        data: data array
        size: array's size
        */
        template<typename T>
        struct Data
        {
            /*data array*/
            const T *data;
            /*array's size*/
            unsigned int size;

            /*
            Data constructor
            data: data array
            size: array's size
            */
            Data(const T *data, unsigned int size)
                    : data(data), size(size) {}
        };
/*
        Load data to VAO and return a model that can be rendered
        positions: Data object containing float[] and size of array
        texCoords: Data object containing float[] and size of array
        indices: Data object containing unsigned int[] and size of array
        threeDimension: Is object in 3 dimensions
        */
        std::shared_ptr<Model> DataToVAO(const Data<float> &positions,
                                         const Data<float> &texCoords,
                                         const Data<unsigned int> &indices,
                                         bool threeDimension);

        /*
        Load data to VAO and return a model that can be rendered
        positions: Data object containing float[] and size of array
        texCoords: Data object containing float[] and size of array
        normals: Data object containing float[] and size of array
        indices: Data object containing unsigned int[] and size of array
        */
        std::shared_ptr<Model> DataToVAO(const Data<float> &positions,
                                         const Data<float> &texCoords,
                                         const Data<float> &normals,
                                         const Data<unsigned int> &indices);


        /*
        Load data to VAO and return a model that can be rendered (Without texture)
        positions: Data object containing float[] and size of array
        indices: Data object containing unsigned int[] and size of array
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
    }
}