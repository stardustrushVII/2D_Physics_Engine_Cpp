// (C) 2025 Stardust Softworks
#include "../include/resolution_selector.h"
#include <vector>
#include <iostream>

Resolution selectResolution(SDL_Renderer* renderer, TTF_Font* font, SDL_Window* window) {
    std::vector<Resolution> resolutions = {
        {640, 480, "640 x 480 (480p)"},
        {1280, 720, "1280 x 720 (720p)"},
        {1920, 1080, "1920 x 1080 (1080p)"},
        {2560, 1440, "2560 x 1440 (1440p)"},
        {3440, 1440, "3440 x 1440 (Ultrawide 1440p)"},
        {3840, 2160, "3840 x 2160 (4K)"}
    };

    int selectedIndex = 0;
    bool selecting = true;
    SDL_Event e;

    while (selecting) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        selectedIndex = (selectedIndex - 1 + resolutions.size()) % resolutions.size();
                        break;
                    case SDLK_RIGHT:
                        selectedIndex = (selectedIndex + 1) % resolutions.size();
                        break;
                    case SDLK_RETURN:
                        selecting = false;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        SDL_RenderClear(renderer);

        SDL_Color white = {255, 255, 255, 255};

        // render logic 1: Big the Cat: Select a stage..
        SDL_Surface* msgSurface = TTF_RenderText_Solid(font, "Please select a resolution.", white);
        SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, msgSurface);
        int msgW, msgH;
        SDL_QueryTexture(msgTexture, nullptr, nullptr, &msgW, &msgH);
        SDL_Rect msgRect = { (640 - msgW) / 2, 100, msgW, msgH }; // position near top
        SDL_RenderCopy(renderer, msgTexture, nullptr, &msgRect);
        SDL_FreeSurface(msgSurface);
        SDL_DestroyTexture(msgTexture);
        SDL_Surface* surface = TTF_RenderText_Solid(font, resolutions[selectedIndex].label, white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        // render logic 2: electric boogaloo
        SDL_Surface* helpSurface = TTF_RenderText_Solid(font, "Use left/right arrow keys then press Enter", white);
        SDL_Texture* helpTexture = SDL_CreateTextureFromSurface(renderer, helpSurface);
        int helpW, helpH;
        SDL_QueryTexture(helpTexture, nullptr, nullptr, &helpW, &helpH);
        SDL_Rect helpRect = { (640 - helpW) / 2, 140, helpW, helpH }; // positioned below first line
        SDL_RenderCopy(renderer, helpTexture, nullptr, &helpRect);
        SDL_FreeSurface(helpSurface);
        SDL_DestroyTexture(helpTexture);


        int tw, th;
        SDL_QueryTexture(texture, nullptr, nullptr, &tw, &th);
        SDL_Rect dst = { (640 - tw) / 2, (480 - th) / 2, tw, th };

        SDL_RenderCopy(renderer, texture, nullptr, &dst);
        SDL_RenderPresent(renderer);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        SDL_Delay(16);
    }

    return resolutions[selectedIndex];
}
