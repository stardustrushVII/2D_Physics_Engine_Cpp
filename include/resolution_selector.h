// (C) 2025 Stardust Softworks
#ifndef RESOLUTION_SELECTOR_H
#define RESOLUTION_SELECTOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Resolution {
    int width;
    int height;
    const char* label;
};

Resolution selectResolution(SDL_Renderer* renderer, TTF_Font* font, SDL_Window* window);

#endif
