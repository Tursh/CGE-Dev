/*
 * BoxCollider.cpp
 *
 * Created by tursh on 8/7/19.
*/

#include <Utils/Log.h>
#include "Physics/BoxCollider.h"

namespace CGE::Physics
{

    float BoxCollider::checkIfCollideInAxis(BoxCollider boxCollider, int axis, float movement)
    {
        //Check if the hitbox are in the same area in the others axis
        for (int i = 1; i <= 2; ++i)
        {
            int otherAxis = (axis + i) % 3;
            //If not they can't collide
            if (boxCollider.posBorder_[otherAxis] <= negBorder_[otherAxis] ||
				boxCollider.negBorder_[otherAxis] >= posBorder_[otherAxis])
                return movement;
        }

        if (movement > 0.0f && boxCollider.posBorder_[axis] <= negBorder_[axis])
        {
            //Get the distance between the moving hitbox and the current hitbox
            float max = negBorder_[axis] - boxCollider.posBorder_[axis];
            //If the movement is higher than the max it can be set it to the max
            if (max < movement)
                movement = max;
        }
        if (movement < 0.0f && boxCollider.negBorder_[axis] >= posBorder_[axis])
        {
            float max = posBorder_[axis] - boxCollider.negBorder_[axis];
            if (max > movement)
                movement = max;
        }

        return movement;
    }

    BoxCollider::BoxCollider(float x0, float x1, float y0, float y1, float z0, float z1)
            : negBorder_(x0, y0, z0), posBorder_(x1, y1, z1) {}

    BoxCollider::BoxCollider(glm::vec3 negBorder, glm::vec3 posBorder)
            : negBorder_(negBorder), posBorder_(posBorder)
    {

    }

    BoxCollider BoxCollider::expand(float scalar)
    {
        return BoxCollider(negBorder_ - glm::vec3(scalar), posBorder_ + glm::vec3(scalar * 2));
    }

	bool BoxCollider::checkCollision(glm::vec3 point)
	{
		return (point.x >= negBorder_.x && point.x <= posBorder_.x &&
				point.y >= negBorder_.y && point.y <= posBorder_.y &&
				point.z >= negBorder_.z && point.z <= posBorder_.z);
	}

}
