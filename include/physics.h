// (C) 2025 Stardust Softworks
#ifndef PHYSICS_H
#define PHYSICS_H

class Player;
class TileMap;

namespace physics {
    void updatePlayer(Player* player, TileMap* tilemap, float deltatime);

    // Constant declarations
    extern const float GRAVITY;
    extern const float MAX_FALL_SPEED;
    extern const float ACCELERATION;
    extern const float DECELERATION;
    extern const float ROLLING_FRICTION;
    extern const float MAX_RUN_SPEED;
    extern const float MAX_RUN_SPEEDL; 
    extern const float JUMP_STRENGTH;

    
}

#endif