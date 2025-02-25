#include <iostream>
#include <SDL3/SDL.h>

#include "renderer/Renderer.hpp"
#include "utils/Vector.hpp"

int main() {
    SDL_Window* mWindow = SDL_CreateWindow("Test", 500, 500, SDL_WINDOW_FULLSCREEN);
    const auto renderer = new Renderer(mWindow);

    const Vector pos = {200, 200};
    const Vector size = {50, 50};

    auto *rect = new SDL_FRect(pos.x, pos.y, size.x, size.y);

    renderer->render_rect(rect, new SDL_Color(255, 0, 0, 255));
    renderer->present();

    SDL_Delay(2000);

    free(rect);

    SDL_DestroyWindow(mWindow);
    SDL_Quit();

    SDL_Quit();
    return 0;
}
