#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#define PARTICLE_SIZE 10

class SimulatableObject
{
public:
    virtual ~SimulatableObject() = default;
    virtual void update(float deltaTime) = 0;
    int x, y;
    float mass, gravity = -9.81f, vy, vx;
};

class Particle : public SimulatableObject
{
public:
    Particle(int x, int y, float vx, float vy);
    ~Particle();
    void update(float deltaTime) override;
};
