// include/player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class TileMap;

class Player {
public:
    float x, y;
    float vx, vy;

    Player(float startX, float startY);
    ~Player();

    void update(TileMap* tilemap, int windowWidth); 
    void render(SDL_Renderer* renderer, int cameraX);

    bool isGrounded = false;
    bool isJumping = false;
};

#endif
