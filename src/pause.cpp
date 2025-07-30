// (C) 2025 Stardust Softworks
#include <SDL2/SDL.h>
#include <iostream>
#include "../include/pause.h"
#include "../include/player.h"
#include <fstream>


// init
TTF_Font* font = TTF_OpenFont("assets/Roboto.ttf", 32);

bool pauseState(bool& pause, SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        std::cout << "Pause state toggled." << std::endl;
        return !pause;
    }
    return pause;
}

void renderPause(SDL_Renderer* renderer, TTF_Font* font) {
    if (!renderer || !font) return;
    // render pause screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128); // semi-transparent black
    SDL_RenderClear(renderer);

    // render pause text
    SDL_Color white = { 255, 255, 255, 255 };

    SDL_Surface* surface = TTF_RenderText_Solid(font, "Paused", white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    int textW = surface->w;
    int textH = surface->h;
    SDL_Rect dstRect = { (640 - textW) / 2, (480 - textH) / 2, textW, textH };
    
    SDL_FreeSurface(surface);
    
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    
    SDL_DestroyTexture(texture);

    
    SDL_RenderPresent(renderer);
}