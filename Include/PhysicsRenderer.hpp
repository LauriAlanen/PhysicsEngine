#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class PhysicsRenderer 
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        PhysicsRenderer(const char* title, int width, int height);
        ~PhysicsRenderer();

        void drawRectangle(int x, int y, int w, int h, SDL_Color color);
        void clearScreen(SDL_Color color);
        void present();
};