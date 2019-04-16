//
// Created by tursh on 1/24/19.
//

#include <string>

#include <Animation/TextureAnimation.h>
#include <tinyxml2.h>
#include <sstream>
#include <iterator>
#include <Utils/XMLElementArrayLoader.h>
#include <Animation/Animator.h>

namespace CGE::Animations
    {

        TextureAnimation::TextureAnimation(const char *filePath)
                : currentAnimation(0), currentTexture(0), frameCountDown(0), idleAnimation(0)
        {
            if (filePath == nullptr)
                return;

            //Construct filePath
            std::string path(ANIMATION_PATH);
            path += filePath;

            tinyxml2::XMLDocument doc;
            //Load our animation file
#ifndef NDEBUG
            auto Succes =
#endif
                    doc.LoadFile(path.data());

#ifndef NDEBUG
            if (Succes != tinyxml2::XML_SUCCESS)
            logError("Anim File at " << path << " does not exist.");
#endif

            std::vector<unsigned int> offsets = Utils::getArray<unsigned int>(
                    doc.RootElement()->FirstChildElement("Offsets")->ToElement());
            for (int i = 0; i < offsets.size(); i += 2)
                textureOffSets.push_back(std::make_pair(offsets[i], offsets[i + 1]));

            frameDuration = Utils::getArray<unsigned int>(doc.RootElement()->FirstChildElement("FrameDuration"));

            //Add to the animator to get updated for each ticks
            Animator::addAnimation(this);
        }
        unsigned int TextureAnimation::getTextureToRender()
        {
            return currentTexture;
        }

        void TextureAnimation::returnToIdle()
        {
            if(currentAnimation != idleAnimation)
            {
                currentAnimation = idleAnimation;
                tick();
            }
        }

        void TextureAnimation::tick()
        {

            //logInfo(frameCountDown << " -> " << currentTexture);
            auto &textureOffSet = textureOffSets[currentAnimation];
            //Is the texture currently in the animation
            if (textureOffSet.first <= currentTexture && currentTexture <= textureOffSet.second)
            {
                if (frameCountDown == 0)
                {
                    //If is was on the last frame return to idle animation
                    if (currentTexture == textureOffSet.second)
                    {
                        currentAnimation = idleAnimation;
                        currentTexture = textureOffSets[idleAnimation].first;
                        frameCountDown = frameDuration[currentTexture];
                    }
                        //Else go to the next frame if the frame count down is done
                    else
                    {
                        currentTexture++;
                        frameCountDown = frameDuration[currentTexture];
                    }
                } else
                    frameCountDown--;
            }
                //If the texture is not in the offset it means that the animation got replaced
            else
                currentTexture = textureOffSet.first;

        }
    }