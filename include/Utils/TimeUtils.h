#pragma once

#include <string>

namespace CGE
{
	namespace Utils
	{

		std::string timeToString(double time, unsigned int microsecondPrecision,
				bool showHours = false);
		void startChrono(unsigned int chronoID);
		void stopChrono(unsigned int chronoID);
		double getChronoTime(unsigned int chronoID);
		void destroyChrono(unsigned int chronoID);

		void resetDelta();
		float getDelta();

		void addFrame();
		float getFPS();

	}
}
