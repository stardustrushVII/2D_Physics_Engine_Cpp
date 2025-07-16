// src/tilemap.cpp (C) 2025 Stardust Software
#include "../include/tilemap.h"

TileMap::TileMap(int w, int h) {
    width = w;
    height = h;
    tiles = new int[width * height];

    for (int i = 0; i < width * height; ++i) {
        tiles[i] = (i / width == height - 1) ? 1 : 0;  // ground on last row
    }
}

TileMap::~TileMap() {
    delete[] tiles;
}

bool TileMap::isSolidTileAt(float worldX, float worldY) {
    int tileX = static_cast<int>(worldX) / 32;
    int tileY = static_cast<int>(worldY) / 32;

    if (tileX < 0 || tileX >= width || tileY < 0 || tileY >= height)
    return false; // enemy out of bounds

    return tiles[tileY * width + tileX] == 1;
}

void TileMap::render(SDL_Renderer* renderer) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tile = tiles[y * width + x];
            if (tile == 1) {
                SDL_Rect rect = { x * 32, y * 32, 32, 32 };
                SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);  // gray block
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
