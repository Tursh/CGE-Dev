//
// Created by tursh on 1/17/19.
//

#include <Renderer/WorldRenderer.h>
#include <Shader/ModelShader/BasicShader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <IO/Display.h>

namespace CGE
{
    namespace Renderer
    {
        namespace WorldRenderer
        {
            Shader::BasicShader *basicShader;
            std::vector<Shader::ShaderProgram *> additionalEntityShaders;
            //TODO: Terrain shaders

            void init()
            {
                basicShader = new CGE::Shader::BasicShader;

                CGE::IO::Display *display = CGE::IO::getDisplay();
                basicShader->start();
                basicShader->loadMatrix(CGE::Shader::PROJECTION,
                                        glm::perspective(45.0f, (float) display->width / display->height, 0.1f, 100.f));
                basicShader->stop();
            }

            void render(const World::World &world)
            {
                glEnable(GL_DEPTH_TEST);
                //First, we render the models without any effects
                basicShader->start();
                basicShader->loadMatrix(Shader::VIEW, world.player->getViewMatrix());
                for (auto entityWithID : world.getEntities())
                {
                    Entities::Entity *entity = entityWithID.second;
                    basicShader->loadMatrix(Shader::TRANSFORMATION, entity->getTransformationMatrix());
                    entity->render();
                }
                basicShader->stop();
                //Then we add the additional effects
                for (auto shader : additionalEntityShaders)
                {


                }
                glDisable(GL_DEPTH_TEST);
            }

        }
    }
}