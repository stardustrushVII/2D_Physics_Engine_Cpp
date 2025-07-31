// (C) 2025 Stardust Softworks
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "../include/player.h"
#include "../include/tilemap.h"
#include "../include/resolution_selector.h"
#include "../include/physics.h"
#include "../include/input.h"
#include "../include/pause.h"

int main(int /*argc*/, char* /*argv*/[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // resolution select window
    SDL_Window* selectorWindow = SDL_CreateWindow("Resolution Select",
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

    // actally game window
    SDL_Window* window = SDL_CreateWindow("Stardust Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        selected.width, selected.height, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int winW = selected.width;
    //int winH = selected.height; 

    int cameraX = 0;
    TileMap* map = new TileMap(50, 15);
    Player* sonic = new Player(100, 100);

    for (int x = 0; x < 50; ++x) {
    map->setTile(x, 13, TileMap::SOLID);
    map->setTile(x, 14, TileMap::SOLID);
    map->setTile(10, 12, TileMap::SLOPE_LEFT);
    map->setTile(11, 12, TileMap::SLOPE_RIGHT);
    map->setTile(12, 11, TileMap::SLOPE_LEFT);
    map->setTile(13, 11, TileMap::SLOPE_RIGHT);
    map->setTile(14, 10, TileMap::SLOPE_LEFT);
    map->setTile(15, 10, TileMap::SLOPE_RIGHT);
    map->setTile(16, 9, TileMap::SLOPE_LEFT);
    map->setTile(17, 9, TileMap::SLOPE_RIGHT);
    map->setTile(18, 8, TileMap::SLOPE_LEFT);
    map->setTile(19, 8, TileMap::SLOPE_RIGHT);
}

    bool running = true;
    bool moveLeft = false;
    bool moveRight = false;
    bool pause = false;

    SDL_Event e;

    // time
    Uint32 lastTicks = SDL_GetTicks();
    float deltaTime = 0.0f;

     while (running) {
        // Calculate deltaTime
        Uint32 currentTicks = SDL_GetTicks(); // Time at the start of the current frame
        deltaTime = (currentTicks - lastTicks) / 1000.0f; // Convert milliseconds to seconds
        lastTicks = currentTicks;

        // handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            pause = pauseState(pause, e);
            if (!pause)
                processPlayerInput(sonic, moveLeft, moveRight, pause, e);
        }

        if (pause) {
            renderPause(renderer, font);
            SDL_RenderPresent(renderer);
            continue;
        }

        // camera logic update
        const int cameraOffsetX = winW / 4;
        cameraX = static_cast<int>(sonic->x) - cameraOffsetX;

        int levelWidth = map->getWidth() * 32;
        if (cameraX < 0) cameraX = 0;
        if (cameraX > levelWidth - winW) cameraX = levelWidth - winW;
        if (cameraX < 0) cameraX = 0; // prevent camera from going out of bounds


        

        // game logic update
        
        sonic->moveLeft = moveLeft;
        sonic->moveRight = moveRight;

        physics::updatePlayer(sonic, map, 0.016f); // frame time budget ~60fps

        // start drawing
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // draw lwvel and player
        map->render(renderer, cameraX);
        sonic->render(renderer, cameraX);

        // render outpit drawn to screen
        SDL_RenderPresent(renderer);

        // debugging code
        std::cout << "x=" << sonic->x << " y=" << sonic->y
                  << " vx=" << sonic->vx << " vy=" << sonic->vy << "\n";

        SDL_Delay(16); // 16.67ms frametime budget
    }

    delete map;
    delete sonic;
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;

    std::cout << "app running, press any key to quit" << std::endl;
    std::cin.get();
}