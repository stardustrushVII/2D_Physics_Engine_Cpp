// include/tilemap.h
#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL2/SDL.h>

class TileMap {

public:
    int width, height;
    int* tiles;

    TileMap(int w, int h);
    ~TileMap();

    void render(SDL_Renderer* renderer);

    bool isSolidTileAt(float worldX, float worldY);
};

#endif
