#include <PhysicsRenderer.hpp>

// #define DEBUG

int PhysicsRenderer::height = 0;
int PhysicsRenderer::width = 0;

PhysicsRenderer::PhysicsRenderer(const char* title) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_Rect displayBounds;
    SDL_GetDisplayBounds(0, &displayBounds);
    PhysicsRenderer::height = displayBounds.y;
    PhysicsRenderer::width = displayBounds.x;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_W, WINDOW_SIZE_H, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    SDL_SetWindowResizable(window, SDL_FALSE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

PhysicsRenderer::~PhysicsRenderer() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void PhysicsRenderer::drawRectangle(int x, int y, int w, int h, SDL_Color color) 
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void PhysicsRenderer::clearScreen(SDL_Color color) 
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void PhysicsRenderer::present() 
{
    SDL_RenderPresent(renderer);
}

void PhysicsRenderer::renderObjects(std::vector<std::unique_ptr<SimulatableObject>> &simulatableObjects)
{
    // Physics engine handles everything using cartesian coordinates so we need to convert to SDL coordinates
    int cartesianX, cartesianY;

    SDL_Color clearColor = {0, 0, 0, 255};
    clearScreen(clearColor);

    for (const auto &simulatableObject : simulatableObjects)
    {
        cartesianX = this->width - simulatableObject->x;
        cartesianY = this->height - simulatableObject->y;
        SDL_Color purple = {128, 0, 128, 255};
        SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, purple.a);
        SDL_Rect rect = {cartesianX, cartesianY, PARTICLE_SIZE, PARTICLE_SIZE};
        SDL_RenderFillRect(renderer, &rect);

        #ifdef DEBUG
        std::cout << "Drawing object at : " << cartesianX << ", " << cartesianY << std::endl;
        #endif
    }
}