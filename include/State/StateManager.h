#pragma once

#include "State.h"

namespace CGE::State::StateManager
{
    /**
     * @return The current game state
     */
    State *getCurrentState();

    /**
     * Delete the current state and replace it with the new state
     * @param newState The new game state
     */
    void setCurrentState(State *newState);

    /**
     * Delete the current state
     */
    void deleteCurrentState();

    /**
     * Delete the current state and replace it with the given state to construct
     * @tparam NewState The new state class to construct
     * @param args The construct arguments
     */
    template<typename NewState, typename... Types>
    void constructAndSetCurrentState(Types... args)
    {
        deleteCurrentState();
        setCurrentState(new NewState(args...));
    }
}
