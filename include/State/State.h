#pragma once

namespace CGE::State
{

    class State
    {
    public:
        /**
         * Called every tick
         */
        virtual void tick() = 0;

        /**
         * Called every render
         */
        virtual void draw() = 0;

        virtual ~State() = default;
    };

}
