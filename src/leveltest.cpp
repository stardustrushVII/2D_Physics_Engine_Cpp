// (C) 2025 Stardust Softworks
#include <SDL2/SDL.h>
#include <iostream>
#include "../include/player.h"
#include "../include/tilemap.h"
#include "../include/physics.h"
#include "../include/input.h"
#include "../include/resolution_selector.h"

int main(int argc, char* argv[]) {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

// resolution select window
    if (TTF_Init() == -1) {
    std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    return 1;
}
    SDL_Window* selectorWindow = SDL_CreateWindow("Stardust_Engine_Resolution_Select",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* selectorRenderer = SDL_CreateRenderer(selectorWindow, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("assets/Roboto.ttf", 32);

    std::cout << "Please Select a Resolution " << std::endl;


    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return 1;
    }

    Resolution selected = selectResolution(selectorRenderer, font, selectorWindow);
    SDL_DestroyRenderer(selectorRenderer);
    SDL_DestroyWindow(selectorWindow);
    TTF_CloseFont(font);

    // create SDL window (for game)
    SDL_Window* window = SDL_CreateWindow("Stardust_Engine_Level_Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        selected.width, selected.height, SDL_WINDOW_SHOWN);
    
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // create SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // create tilemap
    TileMap tilemap(20, 15); // 20x15 tiles

// floor
for (int x = 0; x < 20; ++x) {
    tilemap.setTile(x, 14, TileMap::SOLID);
}

// left slope (ascending right)
tilemap.setTile(5, 13, TileMap::SLOPE_LEFT);
tilemap.setTile(6, 12, TileMap::SLOPE_LEFT);
tilemap.setTile(7, 11, TileMap::SLOPE_LEFT);

// right slope (ascending left)
tilemap.setTile(10, 11, TileMap::SLOPE_RIGHT);
tilemap.setTile(11, 12, TileMap::SLOPE_RIGHT);
tilemap.setTile(12, 13, TileMap::SLOPE_RIGHT);

// flat platform above slopes
for (int x = 5; x <= 12; ++x) {
    tilemap.setTile(x, 10, TileMap::SOLID);
}


    // Creation player and place near the top
    Player sonic(160, 200); // position player above the slope area

    Uint32 lastTicks = SDL_GetTicks();
    bool running = true;
    SDL_Event e;

    bool moveLeft = false;
    bool moveRight = false;
    bool isGrounded = false;
    bool pause = false;


    while (running) {
        // handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;

            }
            processPlayerInput(&sonic, moveLeft, moveRight, pause, e);
        }
        if (moveLeft && !moveRight) sonic.vx = -3.0f;
        else if (moveRight && !moveLeft) sonic.vx = 3.0f;
        else sonic.vx = 0.0f;

        // delta time calculations
        Uint32 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;

        // run physics
        physics::updatePlayer(&sonic, &tilemap, deltaTime);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // render tilemap and player
        tilemap.render(renderer, 0);  // cameraX = 0
        sonic.render(renderer, 0);   // cameraX = 0

        // present current frame
        SDL_RenderPresent(renderer);

        // Debug print
        std::cout << "x=" << sonic.x << " y=" << sonic.y
                  << " vx=" << sonic.vx << " vy=" << sonic.vy << "\n";

        SDL_Delay(16); // 60 16.67ms
    }

    // destruction 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
