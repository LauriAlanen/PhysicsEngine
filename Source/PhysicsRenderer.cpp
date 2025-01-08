#include <PhysicsRenderer.hpp>

int PhysicsRenderer::height = 0;
int PhysicsRenderer::width = 0;

PhysicsRenderer::PhysicsRenderer(const char* title) 
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == 0) 
    {
        spdlog::error("Error initializing SDL: {}", SDL_GetError());
        exit(1);
    }

    if (!SDL_CreateWindowAndRenderer(title, WINDOW_SIZE_W, WINDOW_SIZE_H, 0, &window, &renderer)) 
    {
        spdlog::error("SDL_CreateWindowAndRenderer failed {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        exit(1);
    }
    SDL_GetWindowSize(window, &PhysicsRenderer::width, &PhysicsRenderer::height);

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

void PhysicsRenderer::renderStationary()
{

}

void PhysicsRenderer::renderObjects(std::vector<std::unique_ptr<PhysicsObject>> &physicsObjects, double interpolationFactor)
{
    SDL_Color clearColor = {0, 0, 0, 255};
    clearScreen(clearColor);

    for (const auto &physicsObject : physicsObjects)
    {
        float interpolatedX = physicsObject->previousState.position.x * (1.0f - interpolationFactor) + physicsObject->currentState.position.x * interpolationFactor;
        float interpolatedY = physicsObject->previousState.position.y * (1.0f - interpolationFactor) + physicsObject->currentState.position.y * interpolationFactor;

        float cartesianX = interpolatedX;
        float cartesianY = this->height - interpolatedY;

        SDL_FRect rect = {cartesianX, cartesianY, PARTICLE_SIZE, PARTICLE_SIZE};
        SDL_Color color = {255, 164, 10, 255};
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);

        renderForceVectors(physicsObject, cartesianX + (rect.w / 2), cartesianY + (rect.h / 2));

        spdlog::trace("Interpolation Factor: {:.4f}", interpolationFactor);
        spdlog::trace("Interpolated Position: x = {:.4f}, y = {:.4f}", interpolatedX, interpolatedY);
        spdlog::trace("Converted SDL Coordinates: x = {}, y = {}", cartesianX, cartesianY);
        spdlog::trace("Previous State: x = {}, y = {}, vy = {:.4f}", 
                        physicsObject->previousState.position.x, 
                        physicsObject->previousState.position.y, 
                        physicsObject->previousState.velocity.y);
        spdlog::trace("Current State: x = {}, y = {}, vy = {:.4f}", 
                        physicsObject->currentState.position.x, 
                        physicsObject->currentState.position.y, 
                        physicsObject->currentState.velocity.y);
        spdlog::trace("Rendering object at ({}, {}), color ({}, {}, {}, {})", 
                      cartesianX, cartesianY, color.r, color.g, color.b, color.a);
    }
}

void PhysicsRenderer::drawArrow(int x, int y, int dx, int dy, int arrowHeadLength, int arrowHeadAngle) {
    int x2 = x + dx;
    int y2 = y + dy;
    SDL_RenderLine(renderer, x, y, x2, y2);

    double angle = atan2(dy, dx);
    double leftAngle = angle + M_PI / 180 * arrowHeadAngle;
    double rightAngle = angle - M_PI / 180 * arrowHeadAngle;

    int x3 = x2 - arrowHeadLength * cos(leftAngle);
    int y3 = y2 - arrowHeadLength * sin(leftAngle);

    int x4 = x2 - arrowHeadLength * cos(rightAngle);
    int y4 = y2 - arrowHeadLength * sin(rightAngle);

    SDL_RenderLine(renderer, x2, y2, x3, y3);
    SDL_RenderLine(renderer, x2, y2, x4, y4);
}

void PhysicsRenderer::renderForceVectors(const std::unique_ptr<PhysicsObject>& physicsObject, int x, int y) {
    SDL_Color color = {0, 255, 0, 255}; // Green for force vectors
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int arrowHeadLength = PARTICLE_SIZE;
    int arrowHeadAngle = 30;

    if (physicsObject->magnitudes.up > MAGNITUDE_ARROW_THRESHOLD) 
        drawArrow(x, y, 0, physicsObject->magnitudes.up, arrowHeadLength, arrowHeadAngle); // Up

    if (physicsObject->magnitudes.down > MAGNITUDE_ARROW_THRESHOLD) 
        drawArrow(x, y, 0, -physicsObject->magnitudes.down, arrowHeadLength, arrowHeadAngle);  // Down

    if (physicsObject->magnitudes.right > MAGNITUDE_ARROW_THRESHOLD) 
        drawArrow(x, y, physicsObject->magnitudes.right, 0, arrowHeadLength, arrowHeadAngle);  // Right

    if (physicsObject->magnitudes.left > MAGNITUDE_ARROW_THRESHOLD) 
        drawArrow(x, y, -physicsObject->magnitudes.left, 0, arrowHeadLength, arrowHeadAngle); // Left
}