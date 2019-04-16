#pragma once

#include <string>

namespace CGE::Utils
{

    std::string timeToString(double time, unsigned int microsecondPrecision,
                             bool showHours = false);

    //Chronos

    void startChrono(unsigned int chronoID);

    void stopChrono(unsigned int chronoID);

    double getChronoTime(unsigned int chronoID);

    void destroyChrono(unsigned int chronoID);

    //Frames per second

    void addFrame();

    float getFPS();

    //Ticks per second

    void initTPSClock(unsigned int TPSClockID = 0);

    void terminateTPSClock(unsigned int TPSClockID = 0);

    void resetTPSClock(unsigned int TPSClockID = 0);

    void setTPS(float newTPS, unsigned int TPSClockID = 0);

    float getTPS(unsigned int TPSClockID = 0);

    int getTickCount(unsigned int TPSClockID = 0);

    bool shouldTick(unsigned int TPSClockID = 0);

    float getDelta(unsigned int TPSClockID = 0);

}
