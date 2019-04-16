#pragma once

namespace CGE::State
	{

		class State
		{
		public:
            virtual void tick() = 0;

			virtual void draw() = 0;

			virtual ~State() = default;
		};

	}
