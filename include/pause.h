// (C) 2025 Stardust Softworks
#ifndef PAUSE_H
#define PAUSE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

bool pauseState(bool& pause, SDL_Event& e);
void renderPause(SDL_Renderer* renderer, TTF_Font* font);





#endif
