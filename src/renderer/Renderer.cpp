#include "renderer/Renderer.hpp"
#include <SDL3_image/SDL_image.h>

Renderer::Renderer(SDL_Window *window) {
    sdl_renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);
}

bool Renderer::render_image(const char *file_path, const SDL_FRect *rect) {
    SDL_Texture *texture = IMG_LoadTexture(sdl_renderer, file_path);
    if (texture == nullptr) {
        set_error("Failed to load texture.");
        return false;
    }

    if (!SDL_RenderTexture(sdl_renderer, texture, nullptr, rect)) {
        set_error("SDL error: " + std::string(SDL_GetError()));
        return false;
    }

    return true;
}

bool Renderer::render_rect(const SDL_FRect *rect, const SDL_Color *color) {
    // The color the renderer was on to return to it.
    SDL_Color prev_color;
    SDL_GetRenderDrawColor(sdl_renderer, &prev_color.r, &prev_color.g, &prev_color.b, &prev_color.a);
    SDL_SetRenderDrawColor(sdl_renderer, color->r, color->g, color->b, color->a);

    if (!SDL_RenderFillRect(sdl_renderer, rect)) {
        set_error("SDL error: " + std::string(SDL_GetError()));
        return false;
    }

    SDL_SetRenderDrawColor(sdl_renderer, prev_color.r, prev_color.g, prev_color.b, prev_color.a);
    return true;
}

bool Renderer::render_line(const float x1, const float y1, const float x2, const float y2,
                           const SDL_Color *color) {
    // The color the renderer was on to return to it.
    SDL_Color prev_color;
    SDL_GetRenderDrawColor(sdl_renderer, &prev_color.r, &prev_color.g, &prev_color.b, &prev_color.a);
    SDL_SetRenderDrawColor(sdl_renderer, color->r, color->g, color->b, color->a);

    if (!SDL_RenderLine(sdl_renderer, x1, y1, x2, y2)) {
        set_error("SDL error: " + std::string(SDL_GetError()));
        return false;
    }

    SDL_SetRenderDrawColor(sdl_renderer, prev_color.r, prev_color.g, prev_color.b, prev_color.a);
    return true;
}

bool Renderer::render_point(const float x, const float y, const SDL_Color *color) {
    // The color the renderer was on to return to it.
    SDL_Color prev_color;
    SDL_GetRenderDrawColor(sdl_renderer, &prev_color.r, &prev_color.g, &prev_color.b, &prev_color.a);
    SDL_SetRenderDrawColor(sdl_renderer, color->r, color->g, color->b, color->a);

    if (SDL_RenderPoint(sdl_renderer, x, y)) {
        set_error("SDL error: " + std::string(SDL_GetError()));
        return false;
    }

    SDL_SetRenderDrawColor(sdl_renderer, prev_color.r, prev_color.g, prev_color.b, prev_color.a);
    return true;
}

bool Renderer::present() {
    const bool result = SDL_RenderPresent(sdl_renderer);

    if (!SDL_RenderPresent(sdl_renderer))
        set_error("SDL error: " + std::string(SDL_GetError()));

    return result;
}

void Renderer::set_error(const std::string &error) { this->error = error; }

std::string Renderer::get_error() const { return error; }
