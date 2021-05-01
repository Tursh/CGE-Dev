/*
 * ProjectionMatrix.cpp.cc
 *
 * Created by tursh on 4/30/21.
*/

#include <IO/Window.h>
#include <glm/ext/matrix_clip_space.hpp>
#include "Shader/ProjectionMatrix.h"

namespace CGE::Shader
{

	ProjectionMatrix::ProjectionMatrix(const IO::Window &window, float fov, float zNear, float zFar)
			: FOV_(fov), zNear_(zNear), zFar_(zFar), window_(window)
	{
		recalculate();
	}

	const glm::mat4 &ProjectionMatrix::getMatrix()
	{
		return matrix_;
	}

	void ProjectionMatrix::recalculate()
	{
		matrix_ = glm::perspectiveFov(FOV_, (float) window_.getWidth(), (float) window_.getHeight(), zNear_, zFar_);
	}

	void ProjectionMatrix::setFov(float fov)
	{
		FOV_ = fov;
	}

	void ProjectionMatrix::setZNear(float zNear)
	{
		zNear_ = zNear;
	}

	void ProjectionMatrix::setZFar(float zFar)
	{
		zFar_ = zFar;
	}

	float ProjectionMatrix::getFov() const
	{
		return FOV_;
	}

	float ProjectionMatrix::getZNear() const
	{
		return zNear_;
	}

	float ProjectionMatrix::getZFar() const
	{
		return zFar_;
	}

	const IO::Window &ProjectionMatrix::getWindow() const
	{
		return window_;
	}


}