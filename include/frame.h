#ifndef FNAF2_FRAME_H
#define FNAF2_FRAME_H

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <stdlib.h>
#include "graphics.h"

#define MAX_ANIMATIONS 16

typedef enum game_frame_type
{
    GF_UNKNOWN,
    GF_TITLE,
    GF_OFFICE,
    GF_CAMERA
} game_frame_type_t;

typedef struct game_frame game_frame_t;

struct game_state
{
    game_frame_t* next_frame;
    void* message;
    game_animation_t animations[MAX_ANIMATIONS];
};

struct game_frame
{
    game_frame_type_t type;
    int (*init)(game_state_t*, void* message);
    int (*update)(game_state_t*);
    int (*deinit)(game_state_t*);
};

void change_frame(game_state_t* state, game_frame_t* frame, void* message);

game_frame_t* frame_title(void);
game_frame_t* frame_office(void);
game_frame_t* frame_camera(void);

bool mouse_in_frect(SDL_FRect* frect);

void render_texture(float x, float y, SDL_Texture* texture, SDL_FRect* loc);

#endif
