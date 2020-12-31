/**
 * Created by tursh on 1/17/19.
 */
#pragma once

#include <functional>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <Loader/Texture.h>
#include <Loader/Meshes/TexturedMesh.h>
#include <Physics/Hitbox.h>

/**
 * @brief Entities system
 */
namespace CGE::Entities
{
    /**
     * @brief An entity can be rendered, moved and 2D animated
     */
    class Entity
    {
    protected:
		glm::vec3 ap_;                                         /**< Actual position */
		glm::vec3 op_;                                         /**< Old position */
		glm::vec3 ar_;                                         /**< Actual rotation */
		glm::vec3 or_;                                         /**< Old rotation */
		glm::vec3 as_ = glm::vec3(0);                          /**< Actual speed */
		glm::vec3 os_ = glm::vec3(0);                          /**< Old speed*/
		glm::vec3 aa_ = glm::vec3(0);                          /**< Actual acceleration */
		glm::vec3 oa_ = glm::vec3(0);                          /**< Old acceleration */

        std::vector<std::tuple<int, glm::vec3>> forces_;       /**< List of forces applied on the entity */
        unsigned int ID_;                                      /**< Unique ID */
        Loader::SharedTexMesh texMesh_;                      /**< Textured model */
        bool visible_;                                         /**< Is visible */
        std::function<glm::vec3(Entity *)> checkCollision_;    /**< Collision check function */


	public:
        /**
         * Base Constructor
         * @param texMeshID            Textured model ID
         * @param position              The 3D position of the entity
         * @param rotation              The 3D rotation of the entity (Pitch, Yaw, Roll)
         * @param visible               Is visible
         */
        explicit Entity(unsigned int texMeshID,
                        glm::vec3 position = glm::vec3(0),
                        glm::vec3 rotation = glm::vec3(0),
                        bool visible = true);

        /**
         * Constructor with an already existing textured model
         * @param texMesh              Textured Mesh
         * @param position              The 3D position of the entity
         * @param rotation              The 3D rotation of the entity (Pitch, Yaw, Roll)
         * @param visible               Is visible
         */
        explicit Entity(std::shared_ptr<Loader::TexturedMesh> texMeshID,
                        glm::vec3 position = glm::vec3(0),
                        glm::vec3 rotation = glm::vec3(0),
                        bool visible = true);

        /**
         * Transform the position and rotation to a matrix
         * @return transformation matrix
         */
        glm::mat4 getTransformationMatrix();

        /**
         * Move the actual position by the given movement
         * and replace the old position by the position before the movement
         * @param movement The given movement
         */
        void move(glm::vec3 movement);

        /**
         * Rotate the entity by the vector
         * @param [in] rotation rotation size in radian
         */
        void rotate(glm::vec3 rotation);

        /**
         * Add a force that will change on the speed
         * @param [in] duration         Force duration (in tick)
         * @param [in] power            Power of the force
         */
        void addForce(int duration, glm::vec3 power);

        /**
         * Called every tick.
         * Can be overwritten
         */
        virtual void update();

        /**
         * Called every render.
         * Can be overwritten
         */
        virtual void render();
        
		/**
		 * Set collision function
		 * @param collisionFunc: return the position that respect the collision
		 */
		void setCollisionFunc(const std::function<glm::vec3(Entity*)> &collisionFunc);
  
		//Getters and Setters

        [[nodiscard]] const unsigned int &getID() const;

        void setSpeed(const glm::vec3 &speed);

        [[nodiscard]] const glm::vec3 &getSpeed() const;

        [[nodiscard]] const glm::vec3 &getPosition() const;

        [[nodiscard]] const glm::vec3 &getRotation() const;

        glm::vec3 getRenderPosition();

        glm::vec3 getRenderRotation();

        [[nodiscard]] const glm::vec3 &getOldPosition() const;

        [[nodiscard]] const glm::vec3 &getOldRotation() const;
	
		Physics::Hitbox getHitbox();

        void setTexMesh(const std::shared_ptr<Loader::TexturedMesh> &texMesh);

        [[nodiscard]] const Loader::SharedTexMesh &getTexMesh() const;

        void setVisible(bool visible);

        [[nodiscard]] bool isVisible() const;
        
        virtual const glm::vec3 &getSize();
        
        bool isOnGround();

		virtual bool shouldDie();
        
    };
}
