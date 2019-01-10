#pragma once

#include "State.h"

namespace CGE
{
	namespace State
	{

		namespace stateManager
		{
			State *getCurrentState();

			void setCurrentState(State *newState);

		}

	}
}
