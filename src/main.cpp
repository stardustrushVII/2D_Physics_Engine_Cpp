#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "../include/player.h"
#include "../include/tilemap.h"
#include "../include/resolution_selector.h"

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
    SDL_Window* window = SDL_CreateWindow("Sonic Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        selected.width, selected.height, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int winW = selected.width;
    int winH = selected.height;

    int cameraX = 0;
    TileMap* map = new TileMap(20, 15);
    Player* sonic = new Player(100, 100);

    bool running = true;
    bool moveLeft = false;
    bool moveRight = false;

    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) moveLeft = true;
                if (e.key.keysym.sym == SDLK_RIGHT) moveRight = true;
                if (e.key.keysym.sym == SDLK_SPACE && sonic->isGrounded) {
                    sonic->vy = -10.0f;
                    sonic->isGrounded = false;
                    sonic->isJumping = true;
                }
            }

            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_LEFT) moveLeft = false;
                if (e.key.keysym.sym == SDLK_RIGHT) moveRight = false;
                if (e.key.keysym.sym == SDLK_SPACE) sonic->isJumping = false;
            }
        }

        // camera logic update
        const int cameraOffsetX = winW / 4;
        cameraX = static_cast<int>(sonic->x) - cameraOffsetX;

        int levelWidth = map->getWidth() * 32;
        if (cameraX < 0) cameraX = 0;
        if (cameraX > levelWidth - winW) cameraX = levelWidth - winW;

        // movement controls
        if (moveLeft && !moveRight) sonic->vx = -3.0f;
        else if (moveRight && !moveLeft) sonic->vx = 3.0f;
        else sonic->vx = 0.0f;

        // game logic update
        sonic->update(map, winW);

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
}
