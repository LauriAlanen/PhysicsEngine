#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <SimulatableObjects.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define WINDOW_BORDER_BUFFER 100

struct Bounds {
    int x_min;  
    int y_min;  
    int x_max;  
    int y_max;
};

class PhysicsEngine
{
private:
    Uint64 previousTime, newTime;
    double accumulator, simulationTime;
    std::vector<std::unique_ptr<SimulatableObject>> simulatableObjects;
    Bounds simulationBounds;
    double deltaTime;

public:
    PhysicsEngine(float fps, Bounds simulationBounds);
    ~PhysicsEngine();
    double update();
    void addSimulatableObject(std::unique_ptr<SimulatableObject> object);
    void checkBounds(std::unique_ptr<SimulatableObject> &object);
    std::vector<std::unique_ptr<SimulatableObject>>& getSimulatableObjects();

};

