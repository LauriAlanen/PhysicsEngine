#pragma once

#include <SDL3/SDL.h>
#include <PhysicsEngine.hpp>
#include <PhysicsObjects.hpp>
#include <PhysicsRenderer.hpp>
#include <spdlog/spdlog.h>

#define GRID_SPACING 50

class SpatialHash
{
private:
    PhysicsRenderer& renderer;
    SDL_Texture* texture;
    SDL_Renderer* SDL_renderer;

public:
    SpatialHash(PhysicsRenderer& renderer, BoundingBox boundingBox);
    ~SpatialHash() {}
};