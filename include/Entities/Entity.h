/**
 * Created by tursh on 1/17/19.
 */
#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <Loader/Texture.h>
#include <Loader/Models/TexturedModel.h>

namespace CGE::Entities
{
    /**
     * @brief An entity can be rendered, moved and 2D animated
     */
    class Entity
    {
        glm::vec3 ap_;                                         /**< @var Actual position */
        glm::vec3 op_;                                         /**< Old position */
        glm::vec3 ar_;                                         /**< Actual rotation */
        glm::vec3 or_;                                         /**< Old rotation */
        glm::vec3 as_ = glm::vec3(0);                          /**< Actual speed */
        glm::vec3 os_ = glm::vec3(0);                          /**< Old speed*/
        glm::vec3 aa_ = glm::vec3(0);                          /**< Actual acceleration */
        glm::vec3 oa_ = glm::vec3(0);                          /**< Old acceleration */
    protected:
        std::vector<std::tuple<int, glm::vec3>> forces_;       /**< List of forces applied on the player */
        unsigned int ID_;                                      /**< Unique ID */
        std::shared_ptr<Loader::TexturedModel> texModel_;      /**< Textured model */
        bool visible_;                                         /**< Is visible */
    public:

        /**
         * Base Constructor
         * @param texModelID            Textured model ID
         * @param texturedModelType     Textured model type
         * @param position              The 3D position of the entity
         * @param rotation              The 3D rotation of the entity (Pitch, Yaw, Roll)
         * @param visible               Is visible
         */
        explicit Entity(unsigned int texModelID,
                        glm::vec3 position = {0, 0, 0},
                        glm::vec3 rotation = {0, 0, 0},
                        bool visible = true);

        /**
         * Constructor with an already existing textured model
         * @param texModel              Textured Model
         * @param position              The 3D position of the entity
         * @param rotation              The 3D rotation of the entity (Pitch, Yaw, Roll)
         * @param visible               Is visible
         */
        explicit Entity(std::shared_ptr<Loader::TexturedModel> texModel,
                        glm::vec3 position = glm::vec3(0),
                        glm::vec3 rotation = glm::vec3(0),
                        bool visible = true);

        glm::vec3 getPosition();

        glm::vec3 getRotation();

        /**
         * Transform the position and rotation to a matrix
         * @return transformation matrix
         */
        glm::mat4 getTransformationMatrix();

        void move(glm::vec3 movement);

        /**
         * Add a force that will change on the speed
         * @param [in] duration         Force duration (in tick)
         * @param [in] power            Power of the force
         */
        void addForce(int duration, glm::vec3 power);

        void render();

        unsigned int getID() const;

        void setTexModel(const std::shared_ptr<Loader::TexturedModel> &texModel);

        const std::shared_ptr<Loader::TexturedModel> &getTexModel() const;

        bool isVisible() const;

        void setVisible(bool visible);
    };
}
