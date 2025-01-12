#pragma once

#include <iostream>
#include <math.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <glm/glm.hpp>

#define PARTICLE_SIZE 2.0f
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
    glm::vec2 position = {1.0f, 1.0f};
    glm::vec2 velocity = {1.0f, 1.0f};
    glm::vec2 acceleration = {1.0f, 1.0f};
    glm::vec2 totalForce = {1.0f, 1.0f};  
    glm::vec2 size = {1.0f, 1.0f};
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
    virtual void updateEuler(float deltaTime) = 0;
    virtual void updateVerlet(float deltaTime) = 0;
    virtual void applyDrag() = 0;
    virtual void applyForce(glm::vec2 forceVector) = 0;
    virtual void calculateMagnitudes() = 0;
    BasicState currentState, previousState;
    VectorMagnitudes magnitudes;
};

class Particle : public PhysicsObject
{
public:
    Particle(BasicState currentState);
    ~Particle();
    void updateEuler(float deltaTime) override;
    void updateVerlet(float deltaTime) override;
    void applyDrag() override;
    void applyForce(glm::vec2 forceVector) override;
    void calculateMagnitudes() override;
};
