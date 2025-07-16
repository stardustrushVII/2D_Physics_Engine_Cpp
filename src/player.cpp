// src/player.cpp
#include "../include/player.h"
#include "../include/tilemap.h"

Player::Player(float startX, float startY) {
    x = startX;
    y = startY;
    vx = 0;
    vy = 0;
}

Player::~Player() {
    // Nothing yet — but in future: free textures, sounds, etc.
}

void Player::update(TileMap* tilemap, int windowWidth) {
    vy += 0.5f;  // fake gravity
    y += vy; // vertical position update
    x += vx;

    //---collisionDetection <bottom_center of player>
    float probeX = x + 16;
    float probeY = y + 32;

    if (tilemap->isSolidTileAt(probeX, probeY)) {
        // snapping to nearestTile edge(ware)
        y = static_cast<int>(probeY / 32) * 32 - 32;
        vy = 0;
    }

    x += vx; // horizonatl movement

    if (x < 0) x = 0;
    if (x + 32 > windowWidth) x = windowWidth - 32;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect rect;  
    rect.x = static_cast<int>(x); 
    rect.y = static_cast<int>(y);
    rect.w = 32;
    rect.h = 32;


    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);  // red player
    SDL_RenderFillRect(renderer, &rect);
}
