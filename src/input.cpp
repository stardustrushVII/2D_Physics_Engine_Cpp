// (C) 2025 Stardust Softworks
#include <SDL2/SDL.h>
#include "../include/input.h"
#include "../include/pause.h"

// handle key down event
void processPlayerInput(Player* player, bool& moveLeft, bool& moveRight, bool& pause, SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_LEFT) moveLeft = true;
        if (e.key.keysym.sym == SDLK_RIGHT) moveRight = true;

        // handle pause event
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        pauseState(pause, e);
    }

        if (e.key.keysym.sym == SDLK_SPACE) {
            if (!player->jumpHeld) {
                player->moveJump = true;
                player->jumpHeld = true;
            }
        }
    }

    // handle key release event
    if (e.type == SDL_KEYUP) {
        if (e.key.keysym.sym == SDLK_LEFT) moveLeft = false;
        if (e.key.keysym.sym == SDLK_RIGHT) moveRight = false;

        // variable jump
        if (e.key.keysym.sym == SDLK_SPACE) {
            if (player->vy < 0) {
                player->vy *= 0.5f; // cut jump arc
            }

            // reset jumpHeld so next jump press is allowed
            player->jumpHeld = false;
            player->isJumping = false;
            player->moveJump = false;
        }
    }
}

