// (C) 2025 Stardust Softworks
#ifndef PHYSICS_H
#define PHYSICS_H

class Player;
class TileMap;

namespace physics {
    void updatePlayer(Player* player, TileMap* tilemap, float deltatime);

    
}

#endif