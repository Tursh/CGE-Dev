//
// Created by tursh on 1/24/19.
//

#include <Animation/Animator.h>
#include <vector>

namespace CGE::Animations::Animator
{
    static std::vector<Animation *> animations;

    void addAnimation(Animation *animation)
    {
        animations.push_back(animation);
    }

    void updateAnimations()
    {
        for (auto animation : animations)
        {
            animation->tick();
        }
    }

}
