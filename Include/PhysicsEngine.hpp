#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SDL3/SDL.h>
#include <PhysicsObjects.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define EULER
// #define VERLET

struct BoundingBox
{
    glm::vec2 position;
    float w;
    float h;

    BoundingBox(const glm::vec2& pos = glm::vec2(0.0f, 0.0f), float w = 0.0f, float h = 0.0f)
        : position(pos), w(w), h(h) {}
};


class PhysicsEngine
{
private:
    Uint64 previousTime, newTime;
    double accumulator, simulationTime;
    std::vector<std::unique_ptr<PhysicsObject>> physicsObjects;
    BoundingBox boundingBox;
    double deltaTime;

public:
    PhysicsEngine(float fps, BoundingBox boundingBox);
    ~PhysicsEngine();
    double update();
    void addPhysicsObject(std::unique_ptr<PhysicsObject> object);
    void resolveCollisions(std::unique_ptr<PhysicsObject> &object);
    std::vector<std::unique_ptr<PhysicsObject>>& getPhysicsObjects();
    int getPhysicsObjectCount();
};

