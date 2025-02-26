#include "renderer/Renderer.hpp"
#include "renderer/RendererException.hpp"

Renderer::Renderer(SDL_Window *window) {
    sdl_renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);
}

void Renderer::render_image() {
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
                                " Rect drawn but renderer color refused to change to default.");
    }
}

void Renderer::render_line(const float x1, const float y1, const float x2, const float y2,
                           const SDL_Color *color) const {
    // The color the renderer was on to return to it.
    SDL_Color prev_color;
    SDL_GetRenderDrawColor(sdl_renderer, &prev_color.r, &prev_color.g, &prev_color.b, &prev_color.a);

    if (!SDL_SetRenderDrawColor(sdl_renderer, color->r, color->g, color->b, color->a)
        || !SDL_RenderLine(sdl_renderer, x1, y1, x2, y2)) {
        throw RendererException("SDL Error: " + std::string(SDL_GetError()));
    }

    if (!SDL_SetRenderDrawColor(sdl_renderer, prev_color.r, prev_color.g, prev_color.b, prev_color.a)) {
        throw RendererException("SDL Error: " + std::string(SDL_GetError()) +
                                " Line drawn but renderer color refused to change to default.");
    }
}

void Renderer::render_point(float x, float y, const SDL_Color *color) const {
    // The color the renderer was on to return to it.
    SDL_Color prev_color;
    SDL_GetRenderDrawColor(sdl_renderer, &prev_color.r, &prev_color.g, &prev_color.b, &prev_color.a);

    if (!SDL_SetRenderDrawColor(sdl_renderer, color->r, color->g, color->b, color->a)
        || !SDL_RenderPoint(sdl_renderer, x, y)) {
        throw RendererException("SDL Error: " + std::string(SDL_GetError()));
    }

    if (!SDL_SetRenderDrawColor(sdl_renderer, prev_color.r, prev_color.g, prev_color.b, prev_color.a)) {
        throw RendererException("SDL Error: " + std::string(SDL_GetError()) +
                                " Point drawn but renderer color refused to change to default.");
    }
}

void Renderer::present() const {
    if (!SDL_RenderPresent(sdl_renderer))
        throw RendererException("SDL Error: " + std::string(SDL_GetError()));
}
