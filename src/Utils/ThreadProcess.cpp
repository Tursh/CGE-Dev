/*
 * ThreadProcess.cpp
 *
 * Created by tursh on 9/29/19.
*/

#include "Utils/ThreadProcess.h"

namespace CGE::Utils
{

    void ThreadProcess::wait()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock);
    }

    void ThreadProcess::start()
    {
        running_ = true;
        thread_ = std::thread([&](){run();});
    }

    void ThreadProcess::stop()
    {
        running_ = false;
        cv_.notify_all();
        thread_.join();
    }

    void ThreadProcess::notify()
    {
        cv_.notify_all();
    }
}