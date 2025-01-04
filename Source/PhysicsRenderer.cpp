#include <PhysicsRenderer.hpp>

int PhysicsRenderer::height = 0;
int PhysicsRenderer::width = 0;

PhysicsRenderer::PhysicsRenderer(const char* title, int width, int height) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    PhysicsRenderer::height = height;
    PhysicsRenderer::width = width;

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
    for (const auto &simulatableObject : simulatableObjects)
    {
        SDL_Color purple = {128, 0, 128, 255};
        SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, purple.a);
        SDL_Rect rect = {simulatableObject->x_coordinate, simulatableObject->y_coordinate, PARTICLE_SIZE, PARTICLE_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }
}