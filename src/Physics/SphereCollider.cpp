//
// Created by musique88 on 1/2/21.
//

#include <Utils/MathHelper.h>
#include "Physics/SphereCollider.h"

namespace CGE::Physics
{
	float &SphereCollider::getRadius()
	{
		return radius_;
	}

	glm::vec3 &SphereCollider::getPosition()
	{
		return position_;
	}

	SphereCollider::SphereCollider(glm::vec3 position, float radius)
	:position_(position), radius_(radius)
	{}

	bool SphereCollider::checkCollision(glm::vec3 point)
	{
		return CGE::Util::Math::distance(position_, point) <= radius_;
	}
}
