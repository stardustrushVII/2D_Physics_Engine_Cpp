// (C) 2025 Stardust Softworks
#include "../include/physics.h"
#include "../include/player.h"
#include "../include/tilemap.h"
#include <fstream>
#include <cmath>

namespace physics {

    const float GRAVITY = 0.21875f; // Gravity per frame
    const float MAX_FALL_SPEED = 16.0f; // Terminal velocity
    const float ACCELERATION = 0.046875f; // Ground acceleration
    const float DECELERATION = 0.5f; // Ground deceleration
    const float ROLLING_FRICTION = 0.125f; // Friction when rolling
    const float MAX_RUN_SPEED = 6.0f; // Max running speed
    const float JUMP_STRENGTH = -6.5f; // Initial jump velocity

    void updatePlayer(Player* player, TileMap* tilemap, float /*deltaTime*/) {
        // gravity apply if airbourne
        if (!player->isGrounded) {
            player->vy += GRAVITY;
            if (player->vy > MAX_FALL_SPEED)
                player->vy = MAX_FALL_SPEED;
        }

        // Horizontal movement
        if (player->isGrounded && !player->isRolling) {
            if (player->moveLeft) {
                player->vx -= ACCELERATION;
                if (player->vx < -MAX_RUN_SPEED)
                    player->vx = -MAX_RUN_SPEED;
            } else if (player->moveRight) {
                player->vx += ACCELERATION;
                if (player->vx > MAX_RUN_SPEED)
                    player->vx = MAX_RUN_SPEED;
            } else {
                // Deceleration when no input
                if (player->vx > 0) {
                    player->vx -= DECELERATION;
                    if (player->vx < 0)
                        player->vx = 0;
                } else if (player->vx < 0) {
                    player->vx += DECELERATION;
                    if (player->vx > 0)
                        player->vx = 0;
                }
            }
        }

        // Rolling mechanics
        if (player->isRolling) {
            if (player->vx > 0) {
                player->vx -= ROLLING_FRICTION;
                if (player->vx < 0)
                    player->vx = 0;
            } else if (player->vx < 0) {
                player->vx += ROLLING_FRICTION;
                if (player->vx > 0)
                    player->vx = 0;
            }
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
                // Snap to slope surface
                player->y = slopeY - player->height;
                player->vy = 0;
                player->isGrounded = true;
                player->isJumping = false;

                // Adjust velocity based on slope
                if (tile == TileMap::SLOPE_LEFT)
                    player->vx -= 0.125f; // Simulate rolling down left slope
                else if (tile == TileMap::SLOPE_RIGHT)
                    player->vx += 0.125f; // Simulate rolling down right slope
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

        // Jumping
        if (player->moveJump && player->isGrounded && !player->isJumping) {
            player->vy = JUMP_STRENGTH;
            player->isGrounded = false;
            player->isJumping = true;
        }

        // TODO:: friction
        // TODO:: wall collision
        // TODO:: these physics are dogass, FIX THEM!!
    }

}