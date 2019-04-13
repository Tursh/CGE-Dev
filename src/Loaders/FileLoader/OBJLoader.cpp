/*
 Load OBJ files to a model for rendering
 Author: Raphael Tremblay
 */

#include <glm/ext/vector_float2.hpp>	//glm::vec2
#include <glm/ext/vector_float3.hpp>	//glm::vec3

#include <string>						//std::string
#include <vector>						//std::vector
#include <cstring>
#include <memory>

#include "Loader/Loader.h"                        //loadToVAO
#include "Utils/Log.h"                        //logError

//#define SHOWTIME

#ifdef SHOWTIME
#include <GLFW/glfw3.h>
#endif // SHOWTIME == 1

namespace CGE::Loader
	{

#define MODEL_PATH "res/graphics/models/"

		struct Vertex
		{
			glm::vec3 pos;
			glm::vec2 tex;
			glm::vec3 norm;
			bool isSet = false;
		};

		static inline void processVertex(unsigned int &index, unsigned int &texInd,
				unsigned int &normInd, std::vector<Vertex> &vertices,
				std::vector<unsigned int> &indices, std::vector<glm::vec2> &texs,
				std::vector<glm::vec3> &norms);

        std::shared_ptr<Model> loadOBJFile(const char *filePath)
		{
#ifdef SHOWTIME
			double time = glfwGetTime();
#endif // SHOWTIME == 1

            //Construct filePath
            std::string path(MODEL_PATH);
            path + filePath;

			//Open obj file
			std::FILE *file;
#if 0
			fopen_s(&file, filePath, "r");
#else
			file = fopen(filePath, "r");
#endif
#ifndef NDEBUG
			//Check if the file has been opened correctly
			if (file == NULL)
			{
				//Print if file could not open
				logError("could not open '" << filePath << "'");
			}
#endif

			//Read file
			//Lists
			std::vector<Vertex> vertices;
			std::vector<glm::vec2> in_tex;
			std::vector<glm::vec3> in_norm;
			std::vector<unsigned int> indices;
			//Data read loop
			while (true)
			{
				//Create buffer for the head of the line
				char head[3];
				//Get the head
#if 0
				const int res = fscanf_s(file, "%s", head, 3);
#else
				const int res = fscanf(file, "%s", head, 3);
#endif
				//Check if it's the end of file (EOF)
				if (res == EOF)
					break;
				//Load position
				if (strcmp(head, "v") == 0)
				{
					Vertex vertex;
					fscanf(file, "%f %f %f\n", &vertex.pos.x, &vertex.pos.y, &vertex.pos.z);
					vertices.push_back(vertex);
				}
				//Load texCoord
				else if (strcmp(head, "vt") == 0)
				{
					glm::vec2 tex;
					fscanf(file, "%f %f\n", &tex.x, &tex.y);
					in_tex.push_back(tex);
				}
				//Load normal
				else if (strcmp(head, "vn") == 0)
				{
					glm::vec3 norm;
					fscanf(file, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
					in_norm.push_back(norm);
				}
				//Load indices
				else if (strcmp(head, "f") == 0)
				{
					//Get data
					unsigned int ind_pos[3], ind_tex[3], ind_norm[3];
#ifndef NDEBUG
					int matches =
#endif
							fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &ind_pos[0], &ind_tex[0],
									&ind_norm[0], &ind_pos[1], &ind_tex[1], &ind_norm[1],
									&ind_pos[2], &ind_tex[2], &ind_norm[2]);
#ifndef NDEBUG
					//Look if the 3D model is made of triangles
					if (matches != 9)
					{
						std::cout
								<< "[ERROR] The model is not made of triangles, look your configuration when you export.";
						std::cin.get();
						exit(-1);
					}
#endif
					//Process the data
					for (int i = 0; i < 3; i++)
						processVertex(ind_pos[i], ind_tex[i], ind_norm[i], vertices, indices,
								in_tex, in_norm);
				}
				else
				{
					char buffer[100];
					fgets(buffer, 100, file);
				}
			}
			//Close obj file
			fclose(file);

			//Vertices -> float[]
			unsigned int *ind = indices.data();
			float *pos = new float[vertices.size() * 3];
			float *tex = new float[vertices.size() * 2];
			float *norm = new float[vertices.size() * 3];
			for (unsigned int i = 0; i < vertices.size(); i++)
			{
				Vertex &vertex = vertices[i];
				//pos -> float[]
				pos[i * 3] = vertex.pos.x;
				pos[i * 3 + 1] = vertex.pos.y;
				pos[i * 3 + 2] = vertex.pos.z;
				//tex -> float[]
				tex[i * 2] = vertex.tex.x;
				tex[i * 2 + 1] = vertex.tex.y;
				//norm -> float[]
				norm[i * 3] = vertex.norm.x;
				norm[i * 3 + 1] = vertex.norm.y;
				norm[i * 3 + 2] = vertex.norm.z;
			}

			//Load to VAO
			//float[] -> Data objects
			const Data<float> positionsData(pos, (unsigned int) (vertices.size()) * 3);
			const Data<float> textureCoordsData(tex, (unsigned int) (vertices.size()) * 2);
			const Data<float> normalsData(norm, (unsigned int) (vertices.size()) * 3);
			const Data<unsigned int> indicesData(ind, (unsigned int) (indices.size()));
			//Data objects -> VAO
            std::shared_ptr<Model> model = DataToVAO(positionsData, textureCoordsData, normalsData, indicesData);
			//Delete loading arrays
			delete[] pos;
			delete[] tex;
			delete[] norm;
			//Deleting vectors
			vertices.clear();
			in_tex.clear();
			in_norm.clear();
			indices.clear();

#ifdef SHOWTIME
			//Show how mush time it took
			std::cout << "Finished to load " << filePath << " in " << glfwGetTime() - time << " seconds." << std::endl;
#endif // SHOWTIME

			return model;
		}

		static inline void processVertex(unsigned int &index, unsigned int &texInd,
				unsigned int &normInd, std::vector<Vertex> &vertices,
				std::vector<unsigned int> &indices, std::vector<glm::vec2> &texs,
				std::vector<glm::vec3> &norms)
		{
			//Get vertex with the same position if there is
			Vertex &currentVertex = vertices[index - 1];
			//If there is no vertex with the same index
			if (!currentVertex.isSet)
			{
				//Create vertex
				currentVertex.tex = texs[texInd - 1];
				currentVertex.norm = norms[normInd - 1];
				currentVertex.isSet = true;
				indices.push_back(index - 1);
			}
			else
			{
				//If the vertex has the same tex and norm
				if (currentVertex.tex == texs[texInd - 1]
						&& currentVertex.norm == norms[normInd - 1])
					//Add the index
					indices.push_back(index - 1);
				else
				{
					//Create a new vertex and store tex and norm
					Vertex newVertex = currentVertex;
					newVertex.tex = texs[texInd - 1];
					newVertex.norm = norms[normInd - 1];
					//Add the index of the new vertex
					indices.push_back((unsigned int) (vertices.size()));
					//Add the vertex to the list of vertices
					vertices.push_back(newVertex);
				}
			}
		}

	}
