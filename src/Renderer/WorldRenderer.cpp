//
// Created by tursh on 1/17/19.
//

#include <Renderer/WorldRenderer.h>
#include <Shader/ModelShader/BasicShader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <IO/Display.h>
#include <World/Terrain/TwoDTerrain.h>

namespace CGE
{
    namespace Renderer
    {
        namespace WorldRenderer
        {
            Shader::BasicShader *basicShader;
            Shader::BasicShader *backgroundShader;
            Shader::BasicShader * terrainShader;
            std::vector<Shader::ShaderProgram *> additionalEntityShaders;
            //TODO: Terrain shaders

            void init()
            {
                basicShader = new CGE::Shader::BasicShader;
                backgroundShader = new Shader::BasicShader;
                terrainShader = new Shader::BasicShader;

                genNewProjectionMatrix();
            }

            void genNewProjectionMatrix()
            {
                CGE::IO::Display *display = CGE::IO::getDisplay();
                glm::mat4 projectionMatrix = glm::perspective(45.0f, (float) display->width / display->height, 0.00001f, 100.f);
                basicShader->start();
                basicShader->loadMatrix(CGE::Shader::PROJECTION, projectionMatrix);
                basicShader->stop();
                terrainShader->start();
                terrainShader->loadMatrix(CGE::Shader::PROJECTION, projectionMatrix);
                terrainShader->stop();
            }

            void render(const World::World &world)
            {

                //glEnable(GL_DEPTH_TEST);
                //Render the terrain
                //First, we render the models without any effects
                if(world.isTwoD())
                {
                    auto twoDTerrain = (Terrain::TwoDTerrain *) world.terrain;
                    //Render background
                    backgroundShader->start();
                    //twoDTerrain->renderBackground();
                    backgroundShader->stop();
                    //Render the terrain
                    terrainShader->start();
                    terrainShader->loadMatrix(Shader::VIEW, world.player->getCamera()->toViewMatrix(world.player));
                    //glm::mat4 test = glm::mat4(1);

                    //terrainShader->loadMatrix(Shader::TRANSFORMATION, test);
                    twoDTerrain->render(terrainShader);
                    terrainShader->stop();
                }

                //Render the entities
                basicShader->start();
                basicShader->loadMatrix(Shader::VIEW, world.player->getCamera()->toViewMatrix(world.player));
                for (auto entityWithID : world.getEntities())
                {
                    auto entity = entityWithID.second;
                    basicShader->loadMatrix(Shader::TRANSFORMATION, entity->getTransformationMatrix());
                    glEnable(GL_BLEND);
                    entity->render();
                    glDisable(GL_BLEND);
                }
                basicShader->stop();
                //Then we add the additional effects
                for (auto shader : additionalEntityShaders)
                {


                }
                //glDisable(GL_DEPTH_TEST);
            }

        }
    }
}