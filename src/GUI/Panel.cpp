#include <utility>


#include <GUI/Panel.h>
#include <GUI/GUIRenderer.h>
#include <glm/ext/matrix_transform.hpp>
#include <Loader/RessourceManager.h>
#include <IO/Input.h>

namespace CGE
{
    namespace GUI
    {

        Panel::Panel(const glm::vec2 position, const glm::vec2 dimension, PanelType type,
                     std::function<void(int key, int usage)> keyCallback)
                : GUIComponent(position, dimension), type_(type), keyCallback(std::move(keyCallback))
        {
            if (type_ != PANEL_INVISIBLE)
                texModel_ = Loader::resManagement::getTexModel(type);
            IO::input::addPanel(this);
        }

        Panel::~Panel()
        {
            for (auto button : buttons_)
                delete button;
            if (type_ != PANEL_INVISIBLE)
                delete texModel_;
            IO::input::removePanel(this);
        }

        void Panel::addButton(Button *newButton)
        {
            newButton->setParent(this);
            buttons_.push_back(newButton);
        }

        void Panel::draw()
        {
            if (visible_)
            {
                if (type_ != PANEL_INVISIBLE)
                {
                    //Get the shader
                    GUIShader *shader = GUIRenderer::getGUIShader();
                    shader->start();
                    //Load the transformation matrix
                    glm::mat4 transMatrix(1);
                    transMatrix = glm::translate(transMatrix, glm::vec3( // @suppress("Invalid arguments")
                            position_.x, position_.y, -1));
                    transMatrix = glm::scale(transMatrix, glm::vec3( // @suppress("Invalid arguments")
                            dimension_.x, dimension_.y, 1));
                    shader->setTransformationMatrix(transMatrix);
                    //Render the panel
                    texModel_->render();
                    shader->stop();
                }


                //Render buttons
                for (auto button : buttons_)
                    button->draw();
            }
        }

        void Panel::checkEvents()
        {
            if (visible_)
            {
                for (auto button : buttons_)
                    button->checkEvent();
            }
        }
    }
}
