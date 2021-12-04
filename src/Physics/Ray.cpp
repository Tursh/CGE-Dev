//
// Created by musique88 on 1/2/21.
//

#include "Physics/Ray.h"

namespace CGE::Physics
{
	Ray::Ray(glm::vec3 position, glm::vec3 direction, float length)
	:position_(position), normalizedDirection_(glm::normalize(direction)), length_(length)
	{}

	Ray::Ray(glm::vec3 positionA, glm::vec3 positionB)
	:position_(positionA), normalizedDirection_(glm::normalize(positionB-positionA)), length_((positionB-positionA).length())
	{}
}
