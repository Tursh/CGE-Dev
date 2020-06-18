
#include <State/StateManager.h>

#include "State/State.h"

namespace CGE::State::StateManager
{
    State *currentState;

    State *getCurrentState()
    {
        return currentState;
    }

    void setCurrentState(State *newState)
    {
        delete currentState;
        //Set the new state
        currentState = newState;
    }

    void deleteCurrentState()
    {
        delete currentState;
        currentState = nullptr;
    }

}
