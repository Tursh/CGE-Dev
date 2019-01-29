#pragma once

namespace CGE
{
	namespace State
	{

		class State
		{
		public:
            virtual void tick() = 0;

			virtual void draw() = 0;

			virtual ~State() = default;
		};

	}
}
