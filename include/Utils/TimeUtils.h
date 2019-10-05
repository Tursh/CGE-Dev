#pragma once

#include <string>

namespace CGE::Utils
{

    std::string timeToString(double time, unsigned int microsecondPrecision,
                             bool showHours = false);

    struct Chrono
    {
        static void start(unsigned int chronoID);

        static void stop(unsigned int chronoID);

        static double getTime(unsigned int chronoID);

        static void destroy(unsigned int chronoID);
    };

    //Frames per second
    void addFrame();

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

        double TPSTime;

        double lastTick;

    public:
        static void init(unsigned int TPSClockID = 0, float wantedTPS = 1 / 60.0f);

        static void terminate(unsigned int TPSClockID = 0);

        static void reset(unsigned int TPSClockID = 0);

        static void setTPS(float newTPS, unsigned int TPSClockID = 0);

        static float getTPS(unsigned int TPSClockID = 0);

        static int getTickCount(unsigned int TPSClockID = 0);

        static bool shouldTick(unsigned int TPSClockID = 0);

        static float getDelta(unsigned int TPSClockID = 0);

    private:
        TPSClock(unsigned int ID, float wantedTPS);


        void resetDelta();

        void addTick();
    };
}
