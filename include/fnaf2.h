#ifndef FNAF2_H
#define FNAF2_H

#include "SDL3/SDL_render.h"

#define SCREEN_WIDTH_RATIO 4
#define SCREEN_HEIGHT_RATIO 3

typedef struct runtime_properties
{
    size_t window_scale;
} runtime_properties_t;

SDL_Renderer* get_renderer(void);
runtime_properties_t* get_runtime_properties(void);
bool is_key_pressed(SDL_Scancode code);

#endif
