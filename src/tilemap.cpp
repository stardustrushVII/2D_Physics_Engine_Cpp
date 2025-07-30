 // (C) 2025 Stardust Softworks
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
    if (tiles) delete[] tiles;
}

bool TileMap::isSolidTileAt(float worldX, float worldY) {
    int tileX = static_cast<int>(worldX) / 32;
    int tileY = static_cast<int>(worldY) / 32;

    if (tileX < 0 || tileX >= width || tileY < 0 || tileY >= height)
    return false; // out of bounds

    return tiles[tileY * width + tileX] == 1;
}

void TileMap::render(SDL_Renderer* renderer, int cameraX) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tile = getTile(x, y);

            SDL_Rect rect = {
                x * 32 - cameraX,
                y * 32,
                32,
                32
            };

            switch (tile) {
                case SOLID:
                    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255); // gray
                    SDL_RenderFillRect(renderer, &rect);
                    break;

                case SLOPE_LEFT:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
                    SDL_RenderFillRect(renderer, &rect);
                    break;

                case SLOPE_RIGHT:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue
                    SDL_RenderFillRect(renderer, &rect);
                    break;

                default:
                    // TODO: Draw transparent overlay (maybe... probably not)
                    break;
            }
        }
    }
}

void TileMap::setTile(int x, int y, int value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y * width + x] = value;
    }
}

int TileMap::getTile(int tileX, int tileY) {
    if (tileX < 0 || tileX >= width || tileY < 0 || tileY >= height) {
        return EMPTY;
    }
    return tiles[tileY * width + tileX];
}


int TileMap::getSlopeHeightAt(int tileX, int tileY, float offsetX) {
    int tile = getTile(tileX, tileY);

    if (tile == SLOPE_LEFT) {
        return
        static_cast<int>(offsetX); // 0 - 31
    } else if (tile == SLOPE_RIGHT) {
        return 32 - 
        static_cast<int>(offsetX); // 32 - 1
    }

    return 0; //not a slope (unfortunately)
    }
