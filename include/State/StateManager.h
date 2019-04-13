#pragma once

#include "State.h"

namespace CGE::State::stateManager
		{
			State *getCurrentState();

			void setCurrentState(State *newState);

			void deleteCurrentState();

            template<typename T, typename... Types>
            void createCurrentState(Types&&... args)
            {
                deleteCurrentState();
                setCurrentState(new T(args...));
            }
		}
