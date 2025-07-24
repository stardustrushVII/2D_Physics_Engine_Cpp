// (C) 2025 Stardust Softworks
#include "../include/physics.h"
#include "../include/player.h"
#include "../include/tilemap.h"
#include <fstream>

namespace physics {

    const float GRAVITY = 0.9f;
    const float TERMINAL_VELOCITY = 12.0f;

    void updatePlayer(Player* player, TileMap* tilemap, float /*deltaTime*/) {
        // gravity apply if airbourne
        if (!player->isGrounded) {
            player->vy += GRAVITY;
            if (player->vy > TERMINAL_VELOCITY)
                player->vy = TERMINAL_VELOCITY;
        }

        // movement
        player->x += player->vx;
        player->y += player->vy;

        // check ground collision
        int centerX = static_cast<int>(player->x + player->width / 2);
        int centerY = static_cast<int>(player->y + player->height / 2);

        int tileX = centerX / 32;
        int tileY = centerY / 32;
        int offsetX = centerX % 32;

        int tile = tilemap->getTile(tileX, tileY);

        // slope tile event handling (barely)
        if (tile == TileMap::SLOPE_LEFT || tile == TileMap::SLOPE_RIGHT) {
            int slopeY = tileY * 32 + tilemap->getSlopeHeightAt(tileX, tileY, offsetX);

            if ((player->y + player->height) > slopeY) {
                // snap to slope surface
                player->y = slopeY - player->height;
                player->vy = 0;
                player->isGrounded = true;
                player->isJumping = false;
            }

            // debugging slope log
            std::ofstream debug("/Users/jamesevans/Documents/cpp-practice/sonic-engine/debug_log.txt", std::ios::app);
            if (debug.is_open()) {
                debug << "[SLOPE COLLISION] Tile: " << tile
                      << " at (" << tileX << ", " << tileY << "), slopeY = " << slopeY
                      << ", playerY = " << player->y + player->height << "\n";
                debug.close();
            }
        }
        // check flat ground
        else if (tilemap->isSolidTileAt(player->x, player->y + player->height)) {
            player->y = (static_cast<int>(player->y + player->height) / 32) * 32 - player->height;
            player->vy = 0;
            player->isGrounded = true;
            player->isJumping = false;
        } else {
            player->isGrounded = false;
        }

        // TODO:: friction
        // TODO:: wall collision
        // TODO:: these physics are dogass, FIX THEM!!
    }

}
