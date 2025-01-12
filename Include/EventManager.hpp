#pragma once

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>
#include <PhysicsRenderer.hpp>
#include <PhysicsEngine.hpp>

class EventManager
{
public:
    EventManager(PhysicsRenderer& renderer, PhysicsEngine& engine, BoundingBox& boundingBox)
        : renderer(renderer), engine(engine), boundingBox(boundingBox), mousePressed(false) {}

    void pollEvents(bool& running);

private:
    PhysicsRenderer& renderer;
    PhysicsEngine& engine;
    BoundingBox& boundingBox;
    bool mousePressed;
    float zoom = 1.0f;
};
