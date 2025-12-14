#ifndef FNAF2_GRAPHICS_H
#define FNAF2_GRAPHICS_H

#include "SDL3/SDL_ttf.h"

typedef struct game_state game_state_t;

typedef enum game_graphic
{
    GG_OFFICE_NORMAL = 93,
    GG_OFFICE_FRONTLIGHT = 124,

    GG_CAMERA_FLIPPER = 96,
    GG_MASK_FLIPPER = 120,

    GG_CAMERA_FLIP_F1 = 115,
    GG_CAMERA_FLIP_F2 = 98,
    GG_CAMERA_FLIP_F3 = 117,
    GG_CAMERA_FLIP_F4 = 100,
    GG_CAMERA_FLIP_F5 = 104,
    GG_CAMERA_FLIP_F6 = 105,
    GG_CAMERA_FLIP_F7 = 106,
    GG_CAMERA_FLIP_F8 = 107,
    GG_CAMERA_FLIP_F9 = 111,
    GG_CAMERA_FLIP_F10 = 113,

    GG_OFFICE_DESK_F1 = 292,
    GG_OFFICE_DESK_F2 = 293,
    GG_OFFICE_DESK_F3 = 294,
    GG_OFFICE_DESK_F4 = 297,

    GG_TITLE_BG_NORMAL = 322,

    GG_STATIC_F1 = 329,
    GG_STATIC_F2 = 330,
    GG_STATIC_F3 = 331,
    GG_STATIC_F4 = 332,
    GG_STATIC_F5 = 333,
    GG_STATIC_F6 = 335,

    GG_NO_ELEMENTS = 815
} game_graphic_t;

typedef enum game_font
{
    F_OCR_A,
    F_NO_ELEMENTS
} game_font_t;

typedef enum font_size
{
    FS_SMALL,
    FS_MEDIUM,
    FS_LARGE,
    FS_TITLE,
    FS_NO_ELEMENTS
} font_size_t;

typedef struct game_animation
{
    uint32_t id;
    float x, y;
    uint64_t start; 
    game_graphic_t* frames;
    size_t frame_count;
    uint64_t interval;
    uint32_t active_frame;
    int (*finish)(game_state_t*);
} game_animation_t;

TTF_Font* get_font(game_font_t font, font_size_t size);
bool unload_font(game_font_t font, font_size_t size);
void unload_all_fonts(void);

SDL_Texture* get_graphic(game_graphic_t g);
bool unload_graphic(game_graphic_t g);
void unload_all_graphics(void);

game_animation_t* start_animation(game_state_t* state, game_animation_t* anim);
bool is_animation_active(game_state_t* state, uint32_t id);
bool render_animation(game_state_t* state, uint32_t id);

#endif
