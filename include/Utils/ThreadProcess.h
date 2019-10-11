/*
 * ThreadProcess.h
 *
 * Created by tursh on 9/29/19.
*/

#pragma once

#include <condition_variable>
#include <thread>

namespace CGE::Utils
{
	
	class ThreadProcess
	{
		/**
		 * Thread variables
		 */
		std::condition_variable cv_;
		std::mutex mtx_;
		std::thread thread_;
	
	protected:
		bool running_ = false;
		
		/**
		 * Main thread function
		 */
		virtual void run() = 0;
		
		/**
		 * Wait to be notified
		 */
		void wait();
	
	public:
		/**
		 * Start the thread
		 */
		void start();
		
		/**
		 * Stop the thread
		 */
		void stop();
		
		/**
		 * If the thread is waiting, resume it
		 */
		void notify();
	};
	
}