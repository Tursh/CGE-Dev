//
// Created by musique88 on 1/2/21.
//

#pragma once


#include <glm/glm.hpp>

namespace CGE::Physics
{
	class Collider
	{
		virtual bool checkCollision(glm::vec3 point) = 0;
	};
}
