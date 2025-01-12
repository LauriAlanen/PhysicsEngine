#pragma once

#include <chrono>
#include <spdlog/spdlog.h>

class FPSTracker 
{
public:
    FPSTracker();
    void updateFPS();

private:
    int frameCount;
    float fps;
    std::chrono::high_resolution_clock::time_point lastTime;
};