#include <SpatialHash.hpp>

SpatialHash::SpatialHash(PhysicsRenderer& renderer, BoundingBox boundingBox) : renderer(renderer)
{
    this->SDL_renderer = renderer.getSDL_Renderer();
    this->texture = renderer.getSDL_Texture();

    SDL_SetRenderTarget(this->SDL_renderer, this->texture);

    SDL_SetRenderDrawColor(this->SDL_renderer, 255, 255, 255, 50);

    for (int x = 0; x <= boundingBox.size.x; x += GRID_SPACING)
    {
        SDL_RenderLine(this->SDL_renderer, x, 0, x, boundingBox.size.y);
    }

    for (int y = 0; y <= boundingBox.size.y; y += GRID_SPACING)
    {
        SDL_RenderLine(this->SDL_renderer, 0, y, boundingBox.size.x, y);
    }

    SDL_SetRenderTarget(this->SDL_renderer, nullptr);
}
