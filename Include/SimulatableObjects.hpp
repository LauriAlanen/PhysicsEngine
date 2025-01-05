#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#define PARTICLE_SIZE 2

class BasicState {
public:
    int x, y;
    float vx, vy;
    float ax, ay;  
    float mass;
    float gravity = -9.81f;

    BasicState(int x = 0, int y = 0, 
          float vx = 0, float vy = 0, 
          float mass = 1.0f)
        : x(x), y(y), vx(vx), vy(vy), mass(mass) {}
};


class SimulatableObject
{
public:
    virtual ~SimulatableObject() = default;
    virtual void update(float deltaTime) = 0;
    BasicState currentState, previousState;
};

class Particle : public SimulatableObject
{
public:
    Particle(int x, int y, float vx, float vy, float mass)
    {
        this->currentState = BasicState(x, y, vx, vy, mass);
    }

    ~Particle();
    void update(float deltaTime) override;
};
