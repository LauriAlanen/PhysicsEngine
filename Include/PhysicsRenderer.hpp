#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include <PhysicsObjects.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define WINDOW_SIZE_W 1800
#define WINDOW_SIZE_H 900

class PhysicsRenderer 
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        PhysicsRenderer(const char* title);
        ~PhysicsRenderer();

        static int width, height;

        void drawRectangle(int x, int y, int w, int h, SDL_Color color);
        void clearScreen(SDL_Color color);
        void present();
        void renderObjects(std::vector<std::unique_ptr<PhysicsObject>> &physicsObjects, double interpolationFactor);
        void drawArrow(SDL_Renderer* renderer, int x, int y, int dx, int dy, int arrowHeadLength, int arrowHeadAngle);
        void renderForceVectors(SDL_Renderer* renderer, const std::unique_ptr<PhysicsObject>& physicsObject, int x, int y);
};
