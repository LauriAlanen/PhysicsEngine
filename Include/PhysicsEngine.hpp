#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <SimulatableObjects.hpp>

struct Bounds {
    int x_min;  
    int y_min;  
    int x_max;  
    int y_max;
};

class PhysicsEngine
{
private:
    Uint64 previousTime;
    double accumulator;
    std::vector<std::unique_ptr<SimulatableObject>> simulatableObjects;
    Bounds simulationBounds;

public:
    double timestep;
    PhysicsEngine(float fps, Bounds simulationBounds);
    ~PhysicsEngine();
    void update();
    void addSimulatableObject(std::unique_ptr<SimulatableObject> object);
    void checkBounds(std::unique_ptr<SimulatableObject> &object);
    std::vector<std::unique_ptr<SimulatableObject>>& getSimulatableObjects();

};

