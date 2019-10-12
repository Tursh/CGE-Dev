/*
 * ThreadProcess.cpp
 *
 * Created by tursh on 9/29/19.
*/

#include <Utils/Log.h>
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
        if (!running_)
        {
            running_ = true;
            thread_ = std::thread([&]()
                                  { run(); });
        } else
        logError("This process is already running");
    }

    void ThreadProcess::stop()
    {
        if (running_)
        {
            running_ = false;
            cv_.notify_all();
            thread_.join();
        } else
        logWarning("This process is not running");
    }

    void ThreadProcess::notify()
    {
        cv_.notify_all();
    }
}