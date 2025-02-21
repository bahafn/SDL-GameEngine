#include <iostream>
#include <SDL3/SDL.h>
#include "utils/Vector.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* mWindow = SDL_CreateWindow("Test", 500, 500, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* mRenderer = SDL_CreateRenderer(mWindow, nullptr);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_RenderClear(mRenderer);

    const Vector pos = {200, 200};
    const Vector size = {50, 50};

    SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
    auto *rect = new SDL_FRect(pos.x, pos.y, size.x, size.y);
    SDL_RenderFillRect(mRenderer, rect);

    SDL_RenderPresent(mRenderer);

    SDL_Delay(2000);

    free(rect);

    SDL_DestroyWindow(mWindow);
    SDL_Quit();

    SDL_Quit();
    return 0;
}
