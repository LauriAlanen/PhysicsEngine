#pragma once

#include <iostream>
#include <math.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define PARTICLE_SIZE 20

struct VectorMagnitudes
{
    float up;
    float right;
    float down;
    float left;
};

struct Drag
{
    float airDensity = 1.225;
    float dragCoefficient = 1;
    float xFdrag;
    float yFdrag;
};

struct BasicState 
{
    float x, y;
    float vx, vy;
    float ax, ay;  
    float Fx, Fy;  
    float mass;
    float area;
    static constexpr float gravity = -9.81f;
    Drag drag;
};

class PhysicsObject
{
public:
    virtual ~PhysicsObject() = default;
    virtual void update(float deltaTime) = 0;
    virtual void applyDrag() = 0;
    BasicState currentState, previousState;
    VectorMagnitudes magnitudes;
};

class Particle : public PhysicsObject
{
public:
    Particle(BasicState currentState)
    {
        this->currentState = currentState;
    }

    ~Particle();
    void update(float deltaTime) override;
    void applyDrag() override;
};
