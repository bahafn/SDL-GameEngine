#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>

class Renderer {
    SDL_Renderer *sdl_renderer;

    /** Saves the last error that occurred in execution. */
    std::string error;

public:
    //
    // Constructors
    //
    explicit Renderer(SDL_Window *window);

    //
    // Methods
    //
    /** @returns true for success or false for fail. Call get_error() for more information. */
    bool render_image(const char *file_path, const SDL_FRect *rect);

    /** @returns true for success or false for fail. Call get_error() for more information. */
    bool render_rect(const SDL_FRect *rect, const SDL_Color *color);

    /** @returns true for success or false for fail. Call get_error() for more information. */
    bool render_line(float x1, float y1, float x2, float y2, const SDL_Color *color);

    /** @returns true for success or false for fail. Call get_error() for more information. */
    bool render_point(float x, float y, const SDL_Color *color);

    /** Updates the screen with any renderer that occurred after the last call.  */
    bool present();

    bool clear();

    void set_error(const std::string &error);

    std::string get_error() const;
};

#endif //RENDERER_H
