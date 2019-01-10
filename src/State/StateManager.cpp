#include "State/State.h"

namespace CGE
{
	namespace State
	{

		namespace stateManager
		{
			State* lastState;
			State* currentState;

			State* getCurrentState()
			{
				//Delete the last state if it was existing
				delete lastState;
				lastState = nullptr;
				//Return the current state
				return currentState;
			}

			void setCurrentState(State* newState)
			{
				//Set the current state on the side to delete after it finish it execution
				lastState = currentState;
				//Set the new state
				currentState = newState;
			}
		}

	}
}
