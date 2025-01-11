#include <PhysicsRenderer.hpp>

int PhysicsRenderer::h = 0;
int PhysicsRenderer::w = 0;

PhysicsRenderer::PhysicsRenderer(const char* title) 
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == 0) 
    {
        spdlog::error("Error initializing SDL: {}", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == 0) 
    {
        printf("Failed to initialize SDL_ttf: %s\n", SDL_GetError());
        exit(1);
    }

    // Load generic use font
    font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (font == NULL) 
    {
        printf("Failed to load font: %s\n", SDL_GetError());
    }

    if (!SDL_CreateWindowAndRenderer(title, WINDOW_SIZE_W, WINDOW_SIZE_H, 0, &window, &renderer)) 
    {
        spdlog::error("SDL_CreateWindowAndRenderer failed {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        exit(1);
    }
    SDL_GetWindowSize(window, &PhysicsRenderer::w, &PhysicsRenderer::h);

    spdlog::trace("PhysicsRenderer initialized successfully");
    spdlog::trace("PhysicsRenderer resources cleaned up");
}

PhysicsRenderer::~PhysicsRenderer() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);  
    SDL_DestroyTexture(texture);  
    SDL_Quit();
}

void PhysicsRenderer::clearScreen() 
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void PhysicsRenderer::present() 
{
    SDL_RenderPresent(renderer);
    spdlog::trace("Presenting rendered frame");
}

void PhysicsRenderer::renderControls(int objectCount)
{
    static int lastObjectCount = -1;
    static SDL_Texture* cachedTexture = nullptr;
    static SDL_FRect cachedRect;

    if (lastObjectCount != objectCount)
    {
        lastObjectCount = objectCount;

        if (cachedTexture)
        {
            SDL_DestroyTexture(cachedTexture);
            cachedTexture = nullptr;
        }

        char text[MAX_TEXT_BUFFER];
        snprintf(text, MAX_TEXT_BUFFER, "Particle count: %d", objectCount);

        color = {255, 255, 255, 255}; // White
        surface = TTF_RenderText_Solid(font, text, strlen(text), color);
        if (!surface)
        {
            SDL_Log("Failed to render text surface: %s", SDL_GetError());
            return;
        }

        cachedTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!cachedTexture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            SDL_DestroySurface(surface);
            return;
        }

        cachedRect = {10, 10, static_cast<float>(surface->w), static_cast<float>(surface->h)};

        SDL_DestroySurface(surface);
    }

    if (cachedTexture)
    {
        SDL_RenderTexture(renderer, cachedTexture, NULL, &cachedRect);
    }
}

void PhysicsRenderer::renderObjects(std::vector<std::unique_ptr<PhysicsObject>> &physicsObjects, double interpolationFactor)
{
    float inverseInterpolationFactor = 1.0f - interpolationFactor;

    color = {10, 150, 170, 255}; // Define particle color once

    for (const auto &physicsObject : physicsObjects)
    {
        const auto &prevState = physicsObject->previousState.position;
        const auto &currState = physicsObject->currentState.position;

        float interpolatedX = prevState.x * inverseInterpolationFactor + currState.x * interpolationFactor;
        float interpolatedY = prevState.y * inverseInterpolationFactor + currState.y * interpolationFactor;

        float cartesianX = interpolatedX;
        float cartesianY = this->h - interpolatedY;

        frect = {cartesianX, cartesianY, PARTICLE_SIZE, PARTICLE_SIZE};
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &frect);

        #ifdef DRAW_FORCE_VECTORS
        renderForceVectors(physicsObject, cartesianX + (frect.w / 2), cartesianY + (frect.h / 2));
        #endif
    }
}

void PhysicsRenderer::drawArrow(int x, int y, int dx, int dy, int arrowHeadLength, int arrowHeadAngle) 
{
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

void PhysicsRenderer::renderForceVectors(const std::unique_ptr<PhysicsObject>& physicsObject, int x, int y) 
{
    color = {0, 255, 0, 255}; // Green for force vectors
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int arrowHeadLength = PARTICLE_SIZE;
    int arrowHeadAngle = 30;

    auto drawForceArrow = [&](int dx, int dy) 
    {
        if (abs(dx) > MAGNITUDE_ARROW_THRESHOLD || abs(dy) > MAGNITUDE_ARROW_THRESHOLD) 
        {
            drawArrow(x, y, dx, dy, arrowHeadLength, arrowHeadAngle);
        }
    };

    drawForceArrow(0, physicsObject->magnitudes.up);     // Up
    drawForceArrow(0, -physicsObject->magnitudes.down);  // Down
    drawForceArrow(physicsObject->magnitudes.right, 0);  // Right
    drawForceArrow(-physicsObject->magnitudes.left, 0);  // Left
}


void PhysicsRenderer::createBoundingBoxTexture(BoundingBox boundingBox)
{
    this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->w, this->h);
    if (!this->texture)
    {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_DestroyTexture(this->texture);
        return;
    }

    SDL_SetRenderTarget(this->renderer, this->texture);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);

    SDL_SetRenderDrawColor(this->renderer, 255, 125, 10, 255); // Set rectangle color
    this->frect = {boundingBox.position.x, boundingBox.position.y, boundingBox.w, boundingBox.h};
    SDL_RenderFillRect(this->renderer, &this->frect);
    
    SDL_SetRenderTarget(this->renderer, nullptr);
}

void PhysicsRenderer::renderTexture()
{
    if (!texture) {
        SDL_Log("No texture available !");
        return;
    }

    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
}