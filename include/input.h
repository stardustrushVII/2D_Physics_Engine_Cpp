// (C) 2025 Stardust Softworks
#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>
#include "player.h"

void processPlayerInput(Player* player, bool& moveLeft, bool &moveRight, SDL_Event& e);

#endif