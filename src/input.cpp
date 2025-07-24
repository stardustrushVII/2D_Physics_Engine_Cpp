// (C) 2025 Stardust Softworks
#include <SDL2/SDL.h>
#include "../include/input.h"
// handle key down event
void processPlayerInput(Player* player, bool& moveLeft, bool &moveRight, SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) moveLeft = true;
                if (e.key.keysym.sym == SDLK_RIGHT) moveRight = true;

                if (e.key.keysym.sym == SDLK_SPACE) {
                    if(!player->jumpHeld && player->isGrounded) {
                    player->vy = -12.5f;
                    player->isGrounded = false;
                    player->isJumping = true;
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
            player->vy *= 0.5; // cut jum arc
        }

            // reset jumpHeld so next jump press is allowed
            player->jumpHeld = false;
            player->isJumping = false;
                
        }
    }
    }
