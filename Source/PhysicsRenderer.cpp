#include <PhysicsRenderer.hpp>

int PhysicsRenderer::height = 0;
int PhysicsRenderer::width = 0;

PhysicsRenderer::PhysicsRenderer(const char* title) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        spdlog::error("Error initializing SDL: {}", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_W, WINDOW_SIZE_H, SDL_WINDOW_SHOWN);
    if (!window) {
        spdlog::error("Error creating SDL window: {}", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    SDL_GetWindowSize(window, &PhysicsRenderer::width, &PhysicsRenderer::height);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        spdlog::error("Error creating SDL renderer: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
    spdlog::trace("PhysicsRenderer initialized successfully");
    spdlog::trace("PhysicsRenderer resources cleaned up");
}

PhysicsRenderer::~PhysicsRenderer() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void PhysicsRenderer::clearScreen(SDL_Color color) 
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    spdlog::trace("Clearing screen with color ({}, {}, {}, {})", color.r, color.g, color.b, color.a);
}

void PhysicsRenderer::present() 
{
    SDL_RenderPresent(renderer);
    spdlog::trace("Presenting rendered frame");
}

void PhysicsRenderer::renderObjects(std::vector<std::unique_ptr<PhysicsObject>> &physicsObjects, double interpolationFactor)
{
    SDL_Color clearColor = {0, 0, 0, 255};
    clearScreen(clearColor);

    for (const auto &physicsObject : physicsObjects)
    {
        float interpolatedX = physicsObject->previousState.x * (1.0f - interpolationFactor) + physicsObject->currentState.x * interpolationFactor;
        float interpolatedY = physicsObject->previousState.y * (1.0f - interpolationFactor) + physicsObject->currentState.y * interpolationFactor;

        float cartesianX = interpolatedX;
        float cartesianY = this->height - interpolatedY;

        SDL_Rect rect = {static_cast<int>(cartesianX), static_cast<int>(cartesianY), PARTICLE_SIZE, PARTICLE_SIZE};
        SDL_Color color = {255, 164, 10, 255};
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);

        spdlog::trace("Interpolation Factor: {:.4f}", interpolationFactor);
        spdlog::trace("Interpolated Position: x = {:.4f}, y = {:.4f}", interpolatedX, interpolatedY);
        spdlog::trace("Converted SDL Coordinates: x = {}, y = {}", cartesianX, cartesianY);
        spdlog::trace("Previous State: x = {}, y = {}, vy = {:.4f}", 
                        physicsObject->previousState.x, 
                        physicsObject->previousState.y, 
                        physicsObject->previousState.vy);
        spdlog::trace("Current State: x = {}, y = {}, vy = {:.4f}", 
                        physicsObject->currentState.x, 
                        physicsObject->currentState.y, 
                        physicsObject->currentState.vy);
        spdlog::trace("Rendering object at ({}, {}), color ({}, {}, {}, {})", 
                      cartesianX, cartesianY, color.r, color.g, color.b, color.a);
    }
}