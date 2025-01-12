#include <TextRenderer.hpp>
#include <PhysicsRenderer.hpp>

TextRenderer::TextRenderer(SDL_Renderer* renderer)
    : renderer(renderer)
{
    TTF_Init();
    char path[MAX_TEXT_BUFFER];
    snprintf(path, MAX_TEXT_BUFFER, "%s%s", SDL_GetBasePath(), FONT_PATH);
    this->font = TTF_OpenFont(path, FONT_SIZE);
}

TextRenderer::~TextRenderer() 
{
    if (cachedTexture) 
    {
        SDL_DestroyTexture(cachedTexture);
    }
}

void TextRenderer::RenderText(const std::string& text, float x, float y, bool reRender) 
{
    if (reRender)
    {
        spdlog::info("Updating Text..");
        if (cachedTexture) 
        {
            SDL_DestroyTexture(cachedTexture);
            cachedTexture = nullptr;
        }

        color = {255, 255, 255, 255}; 
        surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
        if (!surface) 
        {
            spdlog::error("Failed to render text surface: {}", SDL_GetError());
            return;
        }

        cachedTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!cachedTexture) {
            spdlog::error("Failed to create texture: {}", SDL_GetError());
            SDL_DestroySurface(surface);
            return;
        }

        cachedRect = {x, y, static_cast<float>(surface->w), static_cast<float>(surface->h)};
        SDL_DestroySurface(surface);
    }
    
    if (cachedTexture)
    {
        SDL_RenderTexture(renderer, cachedTexture, NULL, &cachedRect);
    }
}
