#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>

class Renderer {
    SDL_Renderer *sdl_renderer;
    std::string error;

public:
    //
    // Constructors
    //
    explicit Renderer(SDL_Window *window);

    //
    // Methods
    //
    bool render_image(const char *file_path, const SDL_FRect *rect);

    bool render_rect(const SDL_FRect *rect, const SDL_Color *color);

    bool render_line(float x1, float y1, float x2, float y2, const SDL_Color *color);

    bool render_point(float x, float y, const SDL_Color *color);

    bool present();

    void set_error(const std::string &error);
};

#endif //RENDERER_H
