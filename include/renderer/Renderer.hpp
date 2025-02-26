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
    void render_image();

    void render_rect(const SDL_FRect *rect, const SDL_Color *color) const;

    void render_line(float x1, float y1, float x2, float y2, const SDL_Color *color) const;

    void render_point(float x, float y, const SDL_Color *color) const;

    void present() const;
};

#endif //RENDERER_H
