//
// Created by musique88 on 1/2/21.
//

#pragma once

#include <glm/vec3.hpp>
#include <cmath>

namespace CGE::Util::Math
{
	float distance(glm::vec3 a, glm::vec3 b)
	{
		return (a - b).length();
	}

	// https://en.wikipedia.org/wiki/Fast_inverse_square_root
	// Returns 1/number, a precision of 1 is at least 99% accurate
	float fastInvSqrt(float number, uint precision)
	{
		long i;
		float x2, y;
		const float threeHalves = 1.5f;

		x2 = number * .5f;
		y = number;
		i = * ( long * ) &y;
		i = 0x5f3759df - (i >> 1);
		y = * ( float * ) &i;
		for(int j = 0; j < precision; j++)
			y = y * (threeHalves - (x2 * y * y));
		return y;
	}
}

