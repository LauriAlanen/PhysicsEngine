#pragma once

#include <iostream>
#include <math.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <glm/glm.hpp>

#define PARTICLE_SIZE 50.0f
#define SCALING_FACTOR 3.0f

struct VectorMagnitudes
{
    float up;
    float right;
    float down;
    float left;
};

struct BasicState 
{
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 velocity = {0.0f, 0.0f};
    glm::vec2 acceleration = {0.0f, 0.0f};
    glm::vec2 totalForce = {0.0f, 0.0f};  
    float mass = 1.0f;
    static constexpr float gravity = -9.81f;
    struct Drag {
        float dragCoefficient = 0.47f;
        float airDensity = 1.225f;
        float area = 1.0f;
    } drag;
};

class PhysicsObject
{
public:
    virtual ~PhysicsObject() = default;
    virtual void update_euler(float deltaTime) = 0;
    virtual void update_verlet(float deltaTime) = 0;
    virtual void applyDrag() = 0;
    virtual void applyForce(glm::vec2 forceVector) = 0;
    virtual void calculateMagnitudes() = 0;
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
    void update_euler(float deltaTime) override;
    void update_verlet(float deltaTime) override;
    void applyDrag() override;
    void applyForce(glm::vec2 forceVector) override;
    void calculateMagnitudes() override;
};
