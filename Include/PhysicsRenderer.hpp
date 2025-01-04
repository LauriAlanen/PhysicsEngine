#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include <SimulatableObjects.hpp>

class PhysicsRenderer 
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        PhysicsRenderer(const char* title, int width, int height);
        ~PhysicsRenderer();

        static int width, height;

        void drawRectangle(int x, int y, int w, int h, SDL_Color color);
        void clearScreen(SDL_Color color);
        void present();
        void renderObjects(std::vector<std::unique_ptr<SimulatableObject>> &simulatableObjects);
};
