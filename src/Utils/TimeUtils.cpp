#include <map>            //map
#include <string>        //to_string
#include <iomanip>        //setprecision

#include <GLFW/glfw3.h>
#include <cmath>
#include <Utils/TimeUtils.h>


#include "Utils/TimeUtils.h"
#include "Utils/Log.h"

#define SECOND_PER_MINUTES 60
#define MINUTES_PER_HOURS 60
#define HOURS_PER_DAYS 24
#define SECOND_PER_HOURS 3600
#define SECOND_PER_DAYS 86400

namespace CGE
{
    namespace Utils
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
                                          std::to_string(seconds).substr(0, 2 + microsecondPrecision)    //Add one digit
                                                         : std::to_string(seconds).substr(0, 3 +
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
                    : ID(ID)
            {
                time = 0;
            }

            ~Chronometer()
            {
                delete beg;
            }

            void start()
            {
                if (beg == nullptr)
                    beg = new double(glfwGetTime());
            }

            void stop()
            {
                if (beg != nullptr)
                    time += glfwGetTime() - *beg;
                else
                    logWarning("A chrono has been stop before being started. ID: " << ID);
                delete beg;
            }

            double getTime() const
            {
                if (beg != nullptr)
                    return time + glfwGetTime() - *beg;
                else
                    return time;
            }

        private:
            unsigned int ID;
            double *beg;
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
                chronos.erase(chronos.find(chronoID));
        }

        float lastTime;

        void resetDelta()
        {
            lastTime = static_cast<float>(glfwGetTime());
        }

        float getDelta()
        {
            return static_cast<float>(glfwGetTime()) - lastTime;
        }

        double time = glfwGetTime();
        int frameCount = 0;
        float lastFPS = 0.0f;

        void addFrame()
        {
            double currentTime = glfwGetTime();
            frameCount++;
            if(currentTime - time >= 1.0f)
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


    }
}
