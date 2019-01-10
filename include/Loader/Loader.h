/*
Load data arrays to a Model for rendering
Load OBJ files to a model for rendering
Author: Raphael Tremblay
*/

#pragma once

#include "Model.h"	//Model

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
		normals: Data object containing float[] and size of array
		indices: Data object containing unsigned int[] and size of array
		*/
		Model *DataToVAO(const Data<float> &positions, const Data<float> &texCoords, const Data<float> &normals,
						 const Data<unsigned int> &indices);

		/*
		Load data to VAO and return a model that can be rendered
		positions: Data object containing float[] and size of array
		texCoords: Data object containing float[] and size of array
		indices: Data object containing unsigned int[] and size of array
		threeDimension: Is object in 3 dimensions
		*/
		Model *DataToVAO(const Data<float> &positions, const Data<float> &texCoords, const Data<unsigned int> &indices,
						 bool threeDimension);

		/*
		Load data to VAO and return a model that can be rendered (Without texture)
		positions: Data object containing float[] and size of array
		indices: Data object containing unsigned int[] and size of array
		threeDimension: Is object in 3 dimensions
		*/
		Model *DataToVAO(const Data<float> &positions, const Data<unsigned int> &indices, bool threeDimension);

		/*
		Load obj file to VAO and return a model that can be rendered
		filePath: path to the file from the project folder
		*/
		Model *loadOBJFile(const char *filePath);

	}
}