//
// Created by musique88 on 1/2/21.
//

#pragma once

#include "Collider.h"

namespace CGE::Physics
{
	class SphereCollider : public Collider
	{
		glm::vec3 position_;
		float radius_;

	public:
		float& getRadius();
		glm::vec3& getPosition();
		SphereCollider(glm::vec3 position, float radius);
		bool checkCollision(glm::vec3 point) override;
	};
}


