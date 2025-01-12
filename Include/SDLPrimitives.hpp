#pragma once

#include <SDL3/SDL.h>
#include <PhysicsRenderer.hpp>

class SDLPrimitives 
{
public:
    SDLPrimitives(PhysicsRenderer& renderer);
    void FillRect(int x, int y, int w, int h);
    void DrawCircle(int centreX, int centreY, int radius);
    void FillCircle(int centreX, int centreY, int radius);
    
private:
    PhysicsRenderer& renderer;
    SDL_Renderer* SDL_renderer;
    void DrawCircleOutline(int centreX, int centreY, int radius);
};
