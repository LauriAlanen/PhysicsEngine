#include <SDLPrimitives.hpp>

SDLPrimitives::SDLPrimitives(PhysicsRenderer& renderer) : renderer(renderer) 
{
    this->SDL_renderer = renderer.getSDL_Renderer();
}

void SDLPrimitives::DrawCircle(int centreX, int centreY, int radius) 
{
    DrawCircleOutline(centreX, centreY, radius);
}

void SDLPrimitives::FillCircle(int centreX, int centreY, int radius) 
{
    int x = radius - 1;
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - radius * 2);

    while (x >= y) {
        SDL_RenderLine(SDL_renderer, centreX + x, centreY - y, centreX - x, centreY - y);
        SDL_RenderLine(SDL_renderer, centreX + x, centreY + y, centreX - x, centreY + y);
        SDL_RenderLine(SDL_renderer, centreX + y, centreY - x, centreX - y, centreY - x);
        SDL_RenderLine(SDL_renderer, centreX + y, centreY + x, centreX - y, centreY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - radius * 2);
        }
    }
}

void SDLPrimitives::DrawCircleOutline(int centreX, int centreY, int radius) 
{
    int x = radius - 1;
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - radius * 2);

    while (x >= y) {
        SDL_RenderPoint(SDL_renderer, centreX + x, centreY - y);
        SDL_RenderPoint(SDL_renderer, centreX + x, centreY + y);
        SDL_RenderPoint(SDL_renderer, centreX - x, centreY - y);
        SDL_RenderPoint(SDL_renderer, centreX - x, centreY + y);
        SDL_RenderPoint(SDL_renderer, centreX + y, centreY - x);
        SDL_RenderPoint(SDL_renderer, centreX + y, centreY + x);
        SDL_RenderPoint(SDL_renderer, centreX - y, centreY - x);
        SDL_RenderPoint(SDL_renderer, centreX - y, centreY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - radius * 2);
        }
    }
}
