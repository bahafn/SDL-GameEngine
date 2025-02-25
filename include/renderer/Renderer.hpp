#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

class Renderer {
    SDL_Renderer *sdl_renderer;

public:
    //
    // Constructors
    //
    explicit Renderer(SDL_Window *window);

    //
    // Methods
    //
    bool render_image();

    void render_rect(const SDL_FRect *rect, const SDL_Color *color) const;

    bool render_line();

    bool render_point();

    bool present() const;
};

#endif //RENDERER_H
