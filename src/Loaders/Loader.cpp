/*
Load data arrays to a Model for rendering
Author: Raphael Tremblay
*/

#include <GL/glew.h>	//GL*

#include <vector>		//std::vector

#include "Utils/GLDebug.h"    //GLCall
#include "Loader/Loader.h"        //Data
#include "Loader/Model.h"        //Model

namespace CGE
{
	namespace Loader
	{

//Model

/*
Model constructor
VAO: VAO ID
VBOs: list of VBOs
vertexCount: number of indices
*/
		Model::Model(unsigned int VAO, std::vector<unsigned int> VBOs, unsigned int vertexCount)
				: VAO(VAO), VBOs(VBOs), vertexCount(vertexCount) {}

/*Delete model (VAO and VBOs too)*/
		void Model::destroy() const
		{
			//Delete VAO
			GLCall(glDeleteVertexArrays(1, &VAO));

			//Delete VBOs
			for (unsigned int VBO : VBOs)
			{
#ifndef NDEBUG
                //Make VBOs invalid for debugging
                //VBO = -1;
#endif // ifndef NDEBUG

				GLCall(glDeleteBuffers(1, &VBO));
			}
		}

/*Bind model*/
		void Model::bind() const
		{
			GLCall(glBindVertexArray(VAO));
		}

/*Render model*/
		void Model::render(bool textured) const
		{
			GLCall(glBindVertexArray(VAO));
			GLCall(glEnableVertexAttribArray(0));
			if (textured)GLCall(glEnableVertexAttribArray(1));
			GLCall(glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr));
			GLCall(glDisableVertexAttribArray(0));
			if (textured)GLCall(glDisableVertexAttribArray(1));
			GLCall(glBindVertexArray(0));
		}



//Loader

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
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size * sizeof(unsigned int), data.data, GL_STATIC_DRAW));
		}

/*
Load data to VAO
index: index pointer (pos -> 0, texCoords -> 1, norm -> 2)
dataSize: size that take one part of data (pos -> 3, tex -> 2, norm -> 3)
data: Data object containing float[] and the size of the array
*/
		static void
		loadDataInAttribArray(const unsigned int &index, const unsigned int &dataSize, const Data<float> &data)
		{
			createVBO(GL_ARRAY_BUFFER);
			GLCall(glBufferData(GL_ARRAY_BUFFER, data.size * sizeof(float), data.data, GL_STATIC_DRAW));
			GLCall(glVertexAttribPointer(index, dataSize, GL_FLOAT, false, 0, nullptr));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

/*
Load data to VAO and return a model that can be rendered
positions: Data object containing float[] and size of array
texCoords: Data object containing float[] and size of array
normals: Data object containing float[] and size of array
indices: Data object containing unsigned int[] and size of array
*/
		Model *DataToVAO(const Data<float> &positions, const Data<float> &texCoords, const Data<float> &normals,
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
			return new Model(VAO, VBOs, indices.size);
		}

/*
Load data to VAO and return a model that can be rendered
positions: Data object containing float[] and size of array
texCoords: Data object containing float[] and size of array
indices: Data object containing unsigned int[] and size of array
threeDimension: Is object in 3 dimensions
*/
		Model *DataToVAO(const Data<float> &positions, const Data<float> &texCoords, const Data<unsigned int> &indices,
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
			return new Model(VAO, VBOs, indices.size);
		}

/*
Load data to VAO and return a model that can be rendered (without texture)
positions: Data object containing float[] and size of array
indices: Data object containing unsigned int[] and size of array
*/
		Model *DataToVAO(const Data<float> &positions, const Data<unsigned int> &indices, bool threeDimension)
		{
			const int VAO = createVAO();
			loadDataInAttribArray(0, threeDimension ? 3 : 2, positions);
			loadIndices(indices);
			GLCall(glBindVertexArray(0));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			const std::vector<unsigned int> VBOs = buffers;
			buffers.clear();
			return new Model(VAO, VBOs, indices.size);

		}

	}
}
