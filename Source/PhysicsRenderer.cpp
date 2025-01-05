#include <PhysicsRenderer.hpp>

// #define DEBUG

int PhysicsRenderer::height = 0;
int PhysicsRenderer::width = 0;

PhysicsRenderer::PhysicsRenderer(const char* title) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        spdlog::error("Error initializing SDL: {}", SDL_GetError());
        exit(1);
    }

    SDL_Rect displayBounds;
    SDL_GetDisplayBounds(0, &displayBounds);
    PhysicsRenderer::height = displayBounds.y;
    PhysicsRenderer::width = displayBounds.x;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_W, WINDOW_SIZE_H, SDL_WINDOW_SHOWN);
    if (!window) {
        spdlog::error("Error creating SDL window: {}", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    SDL_SetWindowResizable(window, SDL_FALSE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        spdlog::error("Error creating SDL renderer: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
    spdlog::info("PhysicsRenderer initialized successfully");
    spdlog::info("PhysicsRenderer resources cleaned up");
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
    spdlog::debug("Clearing screen with color ({}, {}, {}, {})", color.r, color.g, color.b, color.a);
}

void PhysicsRenderer::present() 
{
    SDL_RenderPresent(renderer);
    spdlog::debug("Presenting rendered frame");
}

void PhysicsRenderer::renderObjects(std::vector<std::unique_ptr<SimulatableObject>> &simulatableObjects, double interpolationFactor)
{
    // Physics engine handles everything using cartesian coordinates so we need to convert to SDL coordinates

    SDL_Color clearColor = {0, 0, 0, 255};
    clearScreen(clearColor);

    
    for (const auto &simulatableObject : simulatableObjects)
    {
        spdlog::debug("Previous State: x = {}, y = {}, vy = {:.4f}", 
                        simulatableObject->previousState.x, 
                        simulatableObject->previousState.y, 
                        simulatableObject->previousState.vy);
        spdlog::debug("Current State: x = {}, y = {}, vy = {:.4f}", 
                        simulatableObject->currentState.x, 
                        simulatableObject->currentState.y, 
                        simulatableObject->currentState.vy);
        spdlog::debug("Interpolation Factor: {:.4f}", interpolationFactor);

        float interpolatedX = simulatableObject->previousState.x * (1.0f - interpolationFactor) + simulatableObject->currentState.x * interpolationFactor;
        float interpolatedY = simulatableObject->previousState.y * (1.0f - interpolationFactor) + simulatableObject->currentState.y * interpolationFactor;
        spdlog::debug("Interpolated Position: x = {:.4f}, y = {:.4f}", interpolatedX, interpolatedY);

        int cartesianX = interpolatedX;
        int cartesianY = this->height - interpolatedY;
        spdlog::debug("Converted SDL Coordinates: x = {}, y = {}", cartesianX, cartesianY);

        SDL_Color randomColor = {
            static_cast<Uint8>(rand() % 256), // Random red value between 0 and 255
            static_cast<Uint8>(rand() % 256), // Random green value between 0 and 255
            static_cast<Uint8>(rand() % 256), // Random blue value between 0 and 255
            255                                // Alpha channel set to 255 (fully opaque)
        };
        SDL_SetRenderDrawColor(renderer, randomColor.r, randomColor.g, randomColor.b, randomColor.a);
        SDL_Rect rect = {cartesianX, cartesianY, PARTICLE_SIZE, PARTICLE_SIZE};
        SDL_RenderFillRect(renderer, &rect);
        spdlog::debug("Rendering object at ({}, {}), color ({}, {}, {}, {})", 
                      cartesianX, cartesianY, randomColor.r, randomColor.g, randomColor.b, randomColor.a);
    }
}