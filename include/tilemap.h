// (C) 2025 Stardust Softworks
#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL2/SDL.h>

class TileMap {

public:
enum TileType {
    EMPTY = 0,
    SOLID = 1,
    SLOPE_LEFT = 2,   // bottom-left to top-right
    SLOPE_RIGHT = 3   // top-left to bottom-right
};

    int width, height;
    int* tiles = nullptr;
    int getWidth() const { return width; }
    void setTile(int x, int y, int value);


    TileMap(int w, int h);
    ~TileMap();
    int getSlopeHeightAt(int tileX, int tileY, float offsetX);
    int getTile(int tileX, int tileY);


    void render(SDL_Renderer* renderer, int cameraX);

    bool isSolidTileAt(float worldX, float worldY);



};

#endif
