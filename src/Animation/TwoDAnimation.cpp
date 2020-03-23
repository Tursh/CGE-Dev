//
// Created by tursh on 1/24/19.
//

#include <string>

#include <Animation/TwoDAnimation.h>
#include <tinyxml2.h>
#include <sstream>
#include <iterator>
#include <Utils/XMLElementArrayLoader.h>
#include <Animation/Animator.h>
#include <Utils/Log.h>

namespace CGE::Animations
{

    TwoDAnimation::TwoDAnimation(const char *filePath)
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
            textureOffSets_.push_back(std::make_pair(offsets[i], offsets[i + 1]));

        frameDuration_ = Utils::getArray<unsigned int>(doc.RootElement()->FirstChildElement("FrameDuration"));

        //Add to the animator to get updated for each ticks
        Animator::addAnimation(this);
    }

    unsigned int TwoDAnimation::getTextureToRender()
    {
        return currentTexture;
    }

    void TwoDAnimation::returnToIdle()
    {
        if (currentAnimation_ != idleAnimation_)
        {
            currentAnimation_ = idleAnimation_;
            tick();
        }
    }

    void TwoDAnimation::tick()
    {

        //logInfo(frameCountDown << " -> " << currentTexture);
        auto &textureOffSet = textureOffSets_[currentAnimation_];
        //Is the texture currently in the animation
        if (textureOffSet.first <= currentTexture && currentTexture <= textureOffSet.second)
        {
            if (frameCountDown_ == 0)
            {
                //If is was on the last frame return to idle animation
                if (currentTexture == textureOffSet.second)
                {
                    currentAnimation_ = idleAnimation_;
                    currentTexture = textureOffSets_[idleAnimation_].first;
                    frameCountDown_ = frameDuration_[currentTexture];
                }
                    //Else go to the next frame if the frame count down is done
                else
                {
                    currentTexture++;
                    frameCountDown_ = frameDuration_[currentTexture];
                }
            } else
                frameCountDown_--;
        }
            //If the texture is not in the offset it means that the animation got replaced
        else
            currentTexture = textureOffSet.first;

    }

    unsigned int TwoDAnimation::getCurrentAnimation() const
    {
        return currentAnimation_;
    }

    void TwoDAnimation::setCurrentAnimation(unsigned int currentAnimation)
    {
        currentAnimation_ = currentAnimation;
    }

    unsigned int TwoDAnimation::getIdleAnimation() const
    {
        return idleAnimation_;
    }

    void TwoDAnimation::setIdleAnimation(unsigned int idleAnimation)
    {
        idleAnimation_ = idleAnimation;
    }
}