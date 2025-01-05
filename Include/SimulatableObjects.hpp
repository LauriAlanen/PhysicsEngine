#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define PARTICLE_SIZE 20

class BasicState {
public:
    float  x, y;
    float vx, vy;
    float ax, ay;  
    float mass;
    static constexpr float gravity = -9.81f;

    BasicState(float  x = 0, float  y = 0, 
          float vx = 0, float vy = 0, 
          float mass = 0)
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
    Particle(BasicState currentState)
    {
        this->currentState = currentState;
    }

    ~Particle();
    void update(float deltaTime) override;
};
