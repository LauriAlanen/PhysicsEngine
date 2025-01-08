#pragma once

#include <iostream>
#include <math.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define PARTICLE_SIZE 5
#define SCALING_FACTOR 1.0f

struct VectorMagnitudes
{
    float up;
    float right;
    float down;
    float left;
};

struct Vector2D {
    float x = 0.0f;
    float y = 0.0f;

    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D& operator+=(const Vector2D& other) {
        this->x += other.x;
        this->y += other.y; 
        return *this;       
    }
    
    Vector2D& operator-=(const Vector2D& other) {
        this->x -= other.x;
        this->y -= other.y; 
        return *this;       
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D operator/(float scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2D normalize() const {
        float mag = magnitude();
        return (mag > 0) ? (*this / mag) : Vector2D(0, 0);
    }
};

struct BasicState 
{
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D totalForce;  
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
    virtual void update(float deltaTime) = 0;
    virtual void applyDrag() = 0;
    virtual void applyForce(Vector2D forceVector) = 0;
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
    void applyForce(Vector2D forceVector) override;
};
