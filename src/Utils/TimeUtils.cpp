#include <map>            //map
#include <iomanip>        //setprecision

#include <GLFW/glfw3.h>
#include <cmath>
#include <Utils/TimeUtils.h>
#include <thread>
#include <unordered_map>


#include "Utils/Log.h"

//Constants
static const unsigned int
        SECOND_PER_MINUTES = 60,
        MINUTES_PER_HOURS = 60,
        HOURS_PER_DAYS = 24,
        SECOND_PER_HOURS = 3600,
        SECOND_PER_DAYS = 86400;

namespace CGE::Utils
{

    std::string timeToString(double time, unsigned int microsecondPrecision, bool showHours)
    {
        //Find the number of second (+ microseconds)
        const double seconds = std::fmod(time, SECOND_PER_MINUTES);
        //Check if the precision is too high for a double
        if (microsecondPrecision > 5)
        logError("The microseconds precision is too high");
        //If the seconds are lower than 10 add one digit to keep a symmetrical 2 digit number
        const std::string s_seconds = (seconds < 10) ?
                                      std::string("0") +
                                      std::to_string(seconds).substr(0, 2 + microsecondPrecision -
                                                                        ((microsecondPrecision) ? 0
                                                                                                : 1))    //Add one digit
                                                     : std::to_string(seconds).substr(0, 3 - ((microsecondPrecision)
                                                                                              ? 0 : 1) +
                                                                                         microsecondPrecision);                    //Do nothing
        //Find the number of minutes
        const unsigned int minutes = (static_cast<unsigned int>(time) / SECOND_PER_MINUTES) % MINUTES_PER_HOURS;

        const std::string s_minutes = (minutes < 10) ? std::string("0") + std::to_string(minutes) : std::to_string(
                minutes);
        if (time > SECOND_PER_HOURS || showHours)
        {
            const unsigned int hours = (minutes / MINUTES_PER_HOURS) % HOURS_PER_DAYS;
            if (time < SECOND_PER_DAYS)
            {
                const unsigned int days = (hours / HOURS_PER_DAYS);
                return std::to_string(days) + " days " + std::to_string(hours)
                       + ":" + s_minutes + ":" + s_seconds;
            } else
                return std::to_string(hours) + ":" + s_minutes + ":" + s_seconds;

        } else
            return s_minutes + ":" + s_seconds;
    }

    class Chronometer
    {
    public:
        Chronometer(unsigned int ID) // @suppress("Class members should be properly initialized")
                : ID(ID), beg(0)
        {
            time = 0;
        }

        void start()
        {
            if (beg == 0)
                beg = glfwGetTime();
        }

        void stop()
        {
            if (beg != 0)
                time += glfwGetTime() - beg;
            else
                logWarning("A chrono has been stop before being started. ID: " << ID);
            beg = 0;
        }

        double getTime() const
        {
            if (beg != 0)
                return time + glfwGetTime() - beg;
            else
                return time;
        }

    private:
        unsigned int ID;
        double beg;
        double time;
    };

    std::map<unsigned int, Chronometer *> chronos;

    void startChrono(unsigned int chronoID)
    {
        //Check if the chorno exist
        if (chronos.find(chronoID) == chronos.end())
            chronos[chronoID] = new Chronometer(chronoID);
        chronos[chronoID]->start();
    }

    void stopChrono(unsigned int chronoID)
    {
#ifndef NDEBUG
        //Check if the chrono exist
        if (chronos.find(chronoID) == chronos.end())
        {
            logError("An inexisting chrono can't be stopped! ID: " << chronoID);
        } else
#endif
            chronos[chronoID]->stop();
    }

    double getChronoTime(unsigned int chronoID)
    {
#ifndef NDEBUG
        //Check if the chrono exist
        if (chronos.find(chronoID) == chronos.end())
        {
            logError("An inexisting chrono can't be stopped! ID: " << chronoID);
            return 0.0;
        } else
#endif // DEBUG
            return chronos[chronoID]->getTime();
    }

    void destroyChrono(unsigned chronoID)
    {
#ifndef NDEBUG
        //Check if the chrono exist
        if (chronos.find(chronoID) == chronos.end())
        {
            logError("An inexisting chrono can't be stopped! ID: " << chronoID);
        } else
#endif
            delete chronos[chronoID];
        chronos.erase(chronos.find(chronoID));
    }

    static double time = glfwGetTime();
    static int frameCount = 0;
    static float lastFPS = 0.0f;

    void addFrame()
    {
        double currentTime = glfwGetTime();
        frameCount++;
        if (currentTime - time >= 1.0f)
        {
            lastFPS = frameCount;
            frameCount = 0;
            time += 1.0f;
        }
    }

    float getFPS()
    {
        return lastFPS;
    }

    //Time to wait before the next tick
    static std::unordered_map<unsigned int, float> tickCooldown;
    //Tick count since the TPS got started
    static std::unordered_map<unsigned int, int> tickCount;
    //Tick count from the last tick refresh
    static std::unordered_map<unsigned int, int> lastTickCount;
    //Last ticks per second
    static std::unordered_map<unsigned int, float> lastTPS;
    //Time when the last tick occurred
    static std::unordered_map<unsigned int, double> lastTime;

    void resetDelta(unsigned int TPSClockID)
    {
        lastTime[TPSClockID] = glfwGetTime();
    }

    float getDelta(unsigned int TPSClockID)
    {
        return static_cast<float>((glfwGetTime() - lastTime[TPSClockID]) / tickCooldown[TPSClockID]);
    }


    static std::unordered_map<unsigned int, double> TPSTime;

    void addTick(unsigned int TPSClockID)
    {
        tickCount[TPSClockID]++;
        if (glfwGetTime() - TPSTime[TPSClockID] >= 1.0f)
        {
            lastTPS[TPSClockID] = tickCount[TPSClockID] - lastTickCount[TPSClockID];
            lastTickCount[TPSClockID] = tickCount[TPSClockID];
            TPSTime[TPSClockID] += 1.0f;
        }
        resetDelta(TPSClockID);
    }

    void setTPS(float newTPS, unsigned int TPSClockID)
    {
        tickCooldown[TPSClockID] = 1.0 / newTPS;
    }

    float getTPS(unsigned int TPSClockID)
    {
        return lastTPS[TPSClockID];
    }

    int getTickCount(unsigned int TPSClockID)
    {
        return tickCount[TPSClockID];
    }

    static std::unordered_map<unsigned int, double> lastTick;

    bool shouldTick(unsigned int TPSClockID)
    {
        double deltaTime = glfwGetTime() - lastTick[TPSClockID];
        bool shouldTick = deltaTime >= tickCooldown[TPSClockID];
        if (shouldTick)
        {
            lastTick[TPSClockID] += tickCooldown[TPSClockID];
            addTick(TPSClockID);
        }
        if (deltaTime < tickCooldown[TPSClockID] / 10)
            std::this_thread::__sleep_for(std::chrono::seconds(0),
                                          std::chrono::milliseconds((int) (100 * tickCooldown[TPSClockID])));
        return shouldTick;
    }


    void resetTPSClock(unsigned int TPSClockID)
    {
        lastTick[TPSClockID] = glfwGetTime();
    }

    void initTPSClock(unsigned int TPSClockID)
    {
        float currentTime = glfwGetTime();
        tickCooldown[TPSClockID] = 1 / 60.0f;
        tickCount[TPSClockID] = 0;
        lastTickCount[TPSClockID] = 0;
        lastTPS[TPSClockID] = 0;
        lastTick[TPSClockID] = currentTime;
        lastTime[TPSClockID] = currentTime;
        TPSTime[TPSClockID] = currentTime;
    }

    void terminateTPSClock(unsigned int TPSClockID)
    {
        tickCooldown.erase(TPSClockID);
        tickCount.erase(TPSClockID);
        lastTick.erase(TPSClockID);
        lastTPS.erase(TPSClockID);
        lastTick.erase(TPSClockID);
        lastTime.erase(TPSClockID);
        TPSTime.erase(TPSClockID);
    }

}
