#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <PhysicsObjects.hpp>
#include <PhysicsEngine.hpp>
#include <TextRenderer.hpp>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define WINDOW_SIZE_W 1800
#define WINDOW_SIZE_H 900

#define MAX_TEXT_BUFFER 100
#define DRAW 1
#define NO_DRAW 0

#define MAGNITUDE_ARROW_THRESHOLD 5
// #define DRAW_FORCE_VECTORS

struct Controls
{
    float renderfps;
    float physicsFps;
    int particleCount;
};

class PhysicsRenderer 
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_FRect frect;
        SDL_Rect rect;
        SDL_Color color;
        SDL_Surface* surface;
        TTF_Font* font;
        SDL_Texture* texture;
        float zoom = 1.0f;

    public:
        PhysicsRenderer(const char* title);
        ~PhysicsRenderer();

        static int w, h;

        void clearScreen();
        void present();
        void renderControls(Controls controls);
        void createBoundingBoxTexture(BoundingBox SDL_FRect);
        void renderTexture();
        void renderObjects(std::vector<std::unique_ptr<PhysicsObject>> &physicsObjects, double interpolationFactor);
        void drawArrow(int x, int y, int dx, int dy, int arrowHeadLength, int arrowHeadAngle);
        void renderForceVectors(const std::unique_ptr<PhysicsObject>& physicsObject, int x, int y);
        void handleZoom(SDL_Event& event);
        SDL_Renderer* getSDL_Renderer();
        SDL_Texture* getSDL_Texture();

};

