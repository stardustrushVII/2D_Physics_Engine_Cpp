// (C) 2025 Stardust Softworks
#include "../include/player.h"
#include "../include/tilemap.h"

Player::Player(float startX, float startY) {
    x = startX;
    y = startY;
    vx = 0;
    vy = 0;
}

Player::~Player() {
    // TODO: textures, sound, etc
}

void Player::update(TileMap* tilemap, int windowWidth) { // clearly important ALWAYS LOOK HERE FIRST
    vy += 0.5f;  // fake gravity
    y += vy; // vertical position update
    if (!isJumping && vy < 0){
        vy *= 0.4f;
    }
    x += vx;
    if (vy > 10.0f) vy = 10.0f; // fall speed max

    //---collisionDetection <bottom_center of player>
    float probeX = x + 16;
    float probeY = y + 32;

    if (tilemap->isSolidTileAt(probeX, probeY)) {
        // snapping to nearestTile edge(ware)
        y = static_cast<int>(probeY / 32) * 32 - 32;
        vy = 0;
        isGrounded = true; // rules allow jump
    } else {
        isGrounded = false; // in air
    }

    x += vx; // horizonatl movement

    if (x < 0) x = 0;
    if (x + 32 > windowWidth) x = windowWidth - 32;
}

void Player::render(SDL_Renderer* renderer, int cameraX) {
    SDL_Rect rect;  
    rect.x = static_cast<int>(x) - cameraX; 
    rect.y = static_cast<int>(y);
    rect.w = 32;
    rect.h = 32;


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);  // red player
    SDL_RenderFillRect(renderer, &rect);
}
