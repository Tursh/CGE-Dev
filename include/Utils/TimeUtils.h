#pragma once

#include <string>

namespace CGE::Utils
{
	
	std::string timeToString(double time, unsigned int microsecondPrecision,
							 bool showHours = false);
	
	struct Chrono
	{
		/**
		 * Start the chrono at chronoID
		 * @param chronoID The ID of the chrono
		 */
		static void start(unsigned int chronoID);

		/**
    	 * Stop the chrono at chronoID
    	 * @param chronoID The ID of the chrono
    	 */
		static void stop(unsigned int chronoID);

		/**
    	 * Get the time on the chrono at chronoID
    	 * @param chronoID The ID of the chrono
    	 */
		static double getTime(unsigned int chronoID);

		/**
    	 * Delete the chrono at chronoID
    	 * @param chronoID The ID of the chrono
    	 */
		static void destroy(unsigned int chronoID);
	};
	
	/**
	 * Add frame to the frame counter (Should not be called)
	 */
	void addFrame();
	
	/**
	 * Get how many frame have been added in one second (fps)
	 * @return How mane frame per seconds
	 */
	float getFPS();
	
	
	class TPSClock
	{
		//Time to wait before the next tick
		float tickCooldown;
		//Tick count since the TPS got started
		int tickCount;
		//Tick count from the last tick refresh
		int lastTickCount;
		//Last ticks per second
		float lastTPS;
		//Time when the last tick occurred
		double lastTime;
		//Last time that the TPS got calculated
		double TPSTime;
		//Last time a tick occurred
		double lastTick;
	
	public:
		/**
		 * Initialize the TPS clock at TPSClockID
		 * @param TPSClockID The clock ID
		 * @param wantedTPS The desired TPS
		 */
		static void init(unsigned int TPSClockID = 0, float wantedTPS = 1 / 60.0f);
		
		/**
		 * Terminate the TPS clock at TPSClockID
		 * @param TPSClockID The clock ID
		 */
		static void terminate(unsigned int TPSClockID = 0);
		
		/**
		 * Reset the clock
		 * @param TPSClockID The clock ID
		 */
		static void reset(unsigned int TPSClockID = 0);
		
		/**
		 * Set the desired TPS
		 * @param newTPS The desired TPS
		 * @param TPSClockID The clock ID
		 */
		static void setTPS(float newTPS, unsigned int TPSClockID = 0);
		
		/**
		 * Get how many tick the clock did for last second
		 * @param TPSClockID The clock ID
		 * @return Last tick per second of the clock
		 */
		static float getTPS(unsigned int TPSClockID = 0);
		
		/**
		 * How many time the clock ticked since the start
		 * @param TPSClockID The clock ID
		 * @return The clock tick count
		 */
		static int getTickCount(unsigned int TPSClockID = 0);
		
		/**
		 * Is it time to tick
		 * @param TPSClockID The clock ID
		 * @return Is it time to tick
		 */
		static bool shouldTick(unsigned int TPSClockID = 0, bool waitForNextTick = true);
		
		/**
		 * Get the time since last tick
		 * @param TPSClockID The clock ID
		 * @return The time since last tick
		 */
		static float getDelta(unsigned int TPSClockID = 0);
	
	private:
		TPSClock(unsigned int ID, float wantedTPS);
		
		
		void resetDelta();
		
		void addTick();
	};
}
