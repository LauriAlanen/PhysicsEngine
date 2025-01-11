#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <memory>
#include <PhysicsObjects.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define WINDOW_SIZE_W 1800
#define WINDOW_SIZE_H 900

#define FONT_PATH "Assets/fonts/OpenSans-Regular.ttf"
#define FONT_SIZE 10
#define MAX_TEXT_BUFFER 100

#define MAGNITUDE_ARROW_THRESHOLD 5
// #define DRAW_FORCE_VECTORS

class PhysicsRenderer 
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_FRect frect;
        SDL_Rect rect;
        SDL_Color color;
        SDL_Surface *surface;
        TTF_Font *font;
        SDL_Texture *texture;

    public:
        PhysicsRenderer(const char* title);
        ~PhysicsRenderer();

        static int width, height;

        void clearScreen(SDL_Color color);
        void present();
        void renderControls(int objectCount);
        void renderObjects(std::vector<std::unique_ptr<PhysicsObject>> &physicsObjects, double interpolationFactor);
        void drawArrow(int x, int y, int dx, int dy, int arrowHeadLength, int arrowHeadAngle);
        void renderForceVectors(const std::unique_ptr<PhysicsObject>& physicsObject, int x, int y);
};
