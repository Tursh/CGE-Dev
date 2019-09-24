/*
 * Hitbox.h
 *
 * Created by tursh on 8/7/19.
*/

#pragma once


#include <glm/vec3.hpp>

class Hitbox
{
    glm::vec3 negBorder_;
    glm::vec3 posBorder_;

public:
	/**
	 * Create a hitbox with the delimitation position
	 * @param x0 X min
	 * @param x1 X max
	 * @param y0 Y min
	 * @param y1 Y max
	 * @param z0 Z min
	 * @param z1 Z max
	 */
	Hitbox(float x0, float x1, float y0, float y1, float z0, float z1);
	
	/**
	 * Create a hitbox with the delimitation position vector
	 * @param negBorder negative border {x0, y0, z0}
	 * @param posBorder positive border {x1, y1, z1}
	 */
	Hitbox(glm::vec3 negBorder, glm::vec3 posBorder);
    /**
     * check if this hitbox is colliding with the hitbox of a moving entity
     * @param movingHitbox the hitbox of a moving entity
     * @param axis x: 0, y: 1, z: 2
     * @param movement movement of the moving hitbox in the respective axis
     * @return the movement maximum before colliding
     */
    float checkIfCollideInAxis(Hitbox movingHitbox, int axis, float movement);
    
    Hitbox expand(float scalar);
    
    //Getters and Setters
    
    const glm::vec3 &getNegBorder()
	{
    	return negBorder_;
	}
	
	const glm::vec3 &getPosBorder()
	{
		return posBorder_;
	}
};


