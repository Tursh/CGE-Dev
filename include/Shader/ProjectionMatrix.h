/*
 * ProjectionMatrix.h
 *
 * Created by tursh on 4/30/21.
*/

#pragma once

#include <glm/mat4x4.hpp>

namespace CGE::IO
{
	class Window;
}

namespace CGE::Shader
{

	class ProjectionMatrix
	{
		float FOV_, zNear_, zFar_;

		const IO::Window &window_;

		glm::mat4 matrix_;

	public:
		/**
		 * Create a projectionMatrix object that you can edit and then convert into an actual usable matrix
		 * @param window The window that is gonna be use to render
		 * @param fov Field of view (In degree)
		 * @param zNear Nearest z the camera can see
		 * @param zFar Farthest z the camera can see (View Distance)
		 */
		ProjectionMatrix(const IO::Window &window, float fov = 45.0f, float zNear = 0.000001f, float zFar = 100.0f);

		/**
		 * To 4x4 matrix to be used in a shader
		 * @return The actual matrix for projection
		 */
		const glm::mat4 &getMatrix();

		void recalculate();

		void setFov(float fov);

		void setZNear(float zNear);

		void setZFar(float zFar);

		[[nodiscard]] float getFov() const;

		[[nodiscard]] float getZNear() const;

		[[nodiscard]] float getZFar() const;

		[[nodiscard]] const IO::Window &getWindow() const;

	};

}