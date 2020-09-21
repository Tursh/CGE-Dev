#include <map>

#include <Utils/Log.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <Utils/TimeUtils.h>
#include <thread>
#include <unordered_map>


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
            }
            else
                return std::to_string(hours) + ":" + s_minutes + ":" + s_seconds;

        }
        else
            return s_minutes + ":" + s_seconds;
    }

    class Chronometer
    {
    public:
        explicit Chronometer(unsigned int ID) // @suppress("Class members should be properly initialized")
                : ID(ID), beg(0), time(0)
        {}

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

        void clear()
        {
            time = 0;
            beg = 0;
        }

        [[nodiscard]] double getTime() const
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

    void Chrono::start(unsigned int chronoID)
    {
        //Check if the chorno exist
        if (chronos.find(chronoID) == chronos.end())
            chronos[chronoID] = new Chronometer(chronoID);
        chronos[chronoID]->start();
    }

    void Chrono::stop(unsigned int chronoID)
    {
#ifndef NDEBUG
        //Check if the chrono exist
        if (chronos.find(chronoID) == chronos.end())
        {
            logError("An inexisting chrono can't be stopped! ID: " << chronoID);
        }
        else
#endif
            chronos[chronoID]->stop();
    }

    void Chrono::clear(unsigned int chronoID)
    {
        chronos[chronoID]->clear();
    }

    double Chrono::getTime(unsigned int chronoID)
    {
#ifndef NDEBUG
        //Check if the chrono exist
        if (chronos.find(chronoID) == chronos.end())
        {
            logError("An inexisting chrono can't be stopped! ID: " << chronoID);
            return 0.0;
        }
        else
#endif // DEBUG
            return chronos[chronoID]->getTime();
    }

    void Chrono::destroy(unsigned chronoID)
    {
#ifndef NDEBUG
        //Check if the chrono exist
        if (chronos.find(chronoID) == chronos.end())
        {
            logError("An inexisting chrono can't be stopped! ID: " << chronoID);
        }
        else
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

    static std::unordered_map<unsigned int, TPSClock *> TPSClocks;

    void TPSClock::resetDelta()
    {
        lastTime = glfwGetTime();
    }

    float TPSClock::getDelta(unsigned int TPSClockID)
    {
        TPSClock *tpsClock = TPSClocks[TPSClockID];
        return static_cast<float>((glfwGetTime() - tpsClock->lastTime) / tpsClock->tickCooldown);
    }

    void TPSClock::addTick()
    {
        ++tickCount;
        if (glfwGetTime() - TPSTime >= 1.0f)
        {
            lastTPS = tickCount - lastTickCount;
            lastTickCount = tickCount;
            TPSTime += 1.0f;
        }
        resetDelta();
    }

    void TPSClock::setTPS(float newTPS, unsigned int TPSClockID)
    {
        TPSClocks[TPSClockID]->tickCooldown = 1.0f / newTPS;
    }

    float TPSClock::getTPS(unsigned int TPSClockID)
    {
        return TPSClocks[TPSClockID]->lastTPS;
    }

    int TPSClock::getTickCount(unsigned int TPSClockID)
    {
        return TPSClocks[TPSClockID]->tickCount;
    }


    bool TPSClock::shouldTick(unsigned int TPSClockID, bool waitForNextTick)
    {
        if (TPSClocks.empty())
        {
            logWarning("The TPS clock with ID: " << TPSClockID << "does not exist");
            return false;
        }
        TPSClock *tpsClock = TPSClocks[TPSClockID];
        double deltaTime = glfwGetTime() - tpsClock->lastTick;
        bool shouldTick = deltaTime >= tpsClock->tickCooldown;

        if (shouldTick)
        {
            tpsClock->lastTick += tpsClock->tickCooldown;
            tpsClock->addTick();
        }

        if (waitForNextTick && deltaTime > tpsClock->tickCooldown / 10)
            std::this_thread::sleep_for(std::chrono::milliseconds((int) (100 * tpsClock->tickCooldown)));

        return shouldTick;
    }


    void TPSClock::reset(unsigned int TPSClockID)
    {
        TPSClocks[TPSClockID]->lastTick = glfwGetTime();
    }

    void TPSClock::init(unsigned int TPSClockID, float wantedTPS)
    {
        //Check if TPS clock already exist
        if (TPSClocks.count(TPSClockID) > 0)
#ifndef NDEBUG
        logError("TPS clock " << TPSClockID << " already exist");
#else
        logWarning("TPS clock " << TPSClockID << " already exist");
#endif
        //Create the TPS clock
        TPSClocks[TPSClockID] = new TPSClock(TPSClockID, wantedTPS);
    }

    void TPSClock::terminate(unsigned int TPSClockID)
    {
        delete TPSClocks[TPSClockID];
        TPSClocks.erase(TPSClockID);
    }

    TPSClock::TPSClock(unsigned int ID, float wantedTPS)
    {
        double currentTime = glfwGetTime();
        tickCooldown = 1.0f / wantedTPS;
        tickCount = 0;
        lastTickCount = 0;
        lastTPS = 0;
        lastTick = currentTime;
        lastTime = currentTime;
        TPSTime = currentTime;
    }
}
