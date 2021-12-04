//
// Created by musique88 on 1/2/21.
//

#pragma once

#include <glm/glm.hpp>

namespace CGE::Physics
{
	class Ray
	{
		glm::vec3 position_;
		glm::vec3 normalizedDirection_;
		float length_;
	public:
		Ray(glm::vec3 position, glm::vec3 normalizedDirection, float length_);
		Ray(glm::vec3 positionA, glm::vec3 positionB);
	};
}