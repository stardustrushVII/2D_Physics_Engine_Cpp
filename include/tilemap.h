// include/tilemap.h
#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL2/SDL.h>

class TileMap {

public:
    int width, height;
    int* tiles = nullptr;
    int getWidth() const { return width; }

    TileMap(int w, int h);
    ~TileMap();

    void render(SDL_Renderer* renderer, int cameraX);

    bool isSolidTileAt(float worldX, float worldY);
};

#endif
