#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <spdlog/spdlog.h>

#define FONT_PATH "fonts/OpenSans-Regular.ttf"
#define FONT_SIZE 10

class TextRenderer 
{
public:
    TextRenderer() = default;
    TextRenderer(SDL_Renderer* renderer);
    ~TextRenderer();

    void RenderText(const std::string& text, float x, float y, bool reRender);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Color color;
    SDL_Texture* cachedTexture = nullptr;
    SDL_FRect cachedRect = {0, 0, 0, 0};
};

