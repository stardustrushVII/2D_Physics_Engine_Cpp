// src/main.cpp
#include <SDL2/SDL.h>
#include <iostream>
#include "../include/player.h"
#include "../include/tilemap.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    } // SDL video initialisation

    SDL_Window* window = SDL_CreateWindow("Sonic Engine", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    } // Create Window  (SDL)

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // SDL renderer 

    int winW, winH;
    SDL_GetWindowSize(window, &winW, &winH);

    TileMap* map = new TileMap(20, 15);  // 20x15 tiles
    Player* sonic = new Player(100, 100);  // start at pixel (100, 100) // creating game object (heap)

    bool running = true;
    SDL_Event e;

    bool moveLeft = false;
    bool moveRight = false; // movement key tracking

    // Video Game
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }

            // key being press
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) moveLeft = true;
                if (e.key.keysym.sym == SDLK_RIGHT) moveRight = true;
        }

        // key being release by user
        if (e.type == SDL_KEYUP) {
        if (e.key.keysym.sym == SDLK_LEFT) moveLeft = false;
        if (e.key.keysym.sym == SDLK_RIGHT) moveRight = false;
        }
    }  
        // input-based horiz velocity
        if (moveLeft && !moveRight) sonic->vx = -3.0f;
        else if (moveRight && !moveLeft) sonic->vx = 3.0f; // disabling inpuut prioritisation
        else sonic->vx = 0.0f; // no inputs





        sonic->update(map, winW);  // game logic update

        // start drawing work
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //draw level and player
        map->render(renderer);
        sonic->render(renderer);

        // render output drawn to screen
        SDL_RenderPresent(renderer);

        // 16.67ms frsmetime budgeting
        SDL_Delay(16);

        // debug code
        std::cout << "x=" << sonic->x << " y=" << sonic->y
        << " vx=" << sonic->vx << " vy=" << sonic->vy << "\n";
    }

    delete map;
    delete sonic;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
