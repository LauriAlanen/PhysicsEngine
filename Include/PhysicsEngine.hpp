#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <SimulatableObjects.hpp>

class PhysicsEngine
{
private:
    double previousTime, deltaTime, accumulator;
    std::vector<std::unique_ptr<SimulatableObject>> simulatableObjects;

public:
    double timestep;
    PhysicsEngine(float fps);
    ~PhysicsEngine();
    void update();
    void addSimulatableObject(std::unique_ptr<SimulatableObject> object);
};

