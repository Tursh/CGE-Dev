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
        std::condition_variable cv_;

        std::mutex mtx_;

        std::thread thread_;
    protected:
        bool running_ = false;

        virtual void run() = 0;

        void wait();

    public:
        void start();

        void stop();

        void notify();
    };

}