#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#define PARTICLE_SIZE 10

class SimulatableObject
{
public:
    virtual ~SimulatableObject() = default;
    virtual void update(float deltaTime) = 0;
    int x_coordinate, y_coordinate;
};

class Particle : public SimulatableObject
{
private:
    float position, velocity, gravity = 9.81f;

public:
    Particle(float position, float velocity);
    ~Particle();
    void update(float deltaTime) override;
};
 