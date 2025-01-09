#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include <PhysicsObjects.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define WINDOW_SIZE_W 1800
#define WINDOW_SIZE_H 900

#define MAGNITUDE_ARROW_THRESHOLD 5
// #define DRAW_FORCE_VECTORS

class PhysicsRenderer 
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_FRect rect;
        SDL_Color color;

    public:
        PhysicsRenderer(const char* title);
        ~PhysicsRenderer();

        static int width, height;

        void clearScreen(SDL_Color color);
        void present();
        void renderStationary();
        void renderObjects(std::vector<std::unique_ptr<PhysicsObject>> &physicsObjects, double interpolationFactor);
        void drawArrow(int x, int y, int dx, int dy, int arrowHeadLength, int arrowHeadAngle);
        void renderForceVectors(const std::unique_ptr<PhysicsObject>& physicsObject, int x, int y);
};
