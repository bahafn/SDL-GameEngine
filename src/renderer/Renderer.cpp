#include "renderer/Renderer.hpp"
#include "renderer/RendererException.hpp"

Renderer::Renderer(SDL_Window *window) {
    sdl_renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);
}

bool Renderer::render_image() {
    return false;
}

void Renderer::render_rect(const SDL_FRect *rect, const SDL_Color *color) const {
    // The color the renderer was on to return to it.
    SDL_Color prev_color;
    SDL_GetRenderDrawColor(sdl_renderer, &prev_color.r, &prev_color.g, &prev_color.b, &prev_color.a);

    if (!SDL_SetRenderDrawColor(sdl_renderer, color->r, color->g, color->b, color->a)
        || !SDL_RenderFillRect(sdl_renderer, rect)) {
        throw RendererException("SDL Error: " + std::string(SDL_GetError()));
    }

    if (!SDL_SetRenderDrawColor(sdl_renderer, prev_color.r, prev_color.g, prev_color.b, prev_color.a)) {
        throw RendererException("SDL Error: " + std::string(SDL_GetError()) +
                                "Rect drawn but renderer color refused to change to default.");
    }
}

bool Renderer::render_line() {
    return false;
}

bool Renderer::render_point() {
    return false;
}

bool Renderer::present() const { return SDL_RenderPresent(sdl_renderer); }
