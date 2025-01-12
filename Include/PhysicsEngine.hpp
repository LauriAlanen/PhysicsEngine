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
    glm::vec2 size;

    BoundingBox(const glm::vec2& pos = glm::vec2(0.0f, 0.0f), const glm::vec2& size = glm::vec2(0.0f, 0.0f))
        : position(pos), size(size) {}
};

class PhysicsEngine
{
private:
    Uint64 previousTime, newTime;
    double accumulator, simulationTime;
    std::vector<std::unique_ptr<PhysicsObject>> physicsObjects;
    double deltaTime;
    BoundingBox boundingBox;

public:
    PhysicsEngine(float fps);
    ~PhysicsEngine();
    double update();
    void addPhysicsObject(std::unique_ptr<PhysicsObject> object);
    void resolveCollisions(std::unique_ptr<PhysicsObject> &object);
    std::vector<std::unique_ptr<PhysicsObject>>& getPhysicsObjects();
    int getPhysicsObjectCount();
    void setBoundingBox(BoundingBox boundingBox);
    void modifyBoundingBox(glm::vec2 position, glm::vec2 size);
    BasicState generateRandomParticle(glm::vec2 position);
};

