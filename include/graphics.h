#ifndef FNAF2_GRAPHICS_H
#define FNAF2_GRAPHICS_H

#include "SDL3/SDL_ttf.h"

typedef struct game_state game_state_t;

typedef enum game_graphic
{
    // Office
    GG_OFFICE_NORMAL = 93,
    GG_OFFICE_FRONT_LIGHT = 124,
    GG_OFFICE_LEFT_LIGHT = 167,
    GG_OFFICE_RIGHT_LIGHT = 169,

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

    // Party Room 1
    GG_CAMERA_CAM1_DARK = 175,
    GG_CAMERA_CAM1_LIT = 190,

    // Party Room 2
    GG_CAMERA_CAM2_DARK = 81,
    GG_CAMERA_CAM2_LIT = 85,
    GG_CAMERA_CAM2_LIT_BONNIE = 182,

    // Party Room 3
    GG_CAMERA_CAM3_DARK = 83,
    GG_CAMERA_CAM3_LIT = 84,
    GG_CAMERA_CAM3_LIT_BONNIE = 86,

    // Party Room 4
    GG_CAMERA_CAM4_DARK = 44,
    GG_CAMERA_CAM4_LIT = 46,

    // Left Air Vent
    GG_CAMERA_CAM5_DARK = 33,
    GG_CAMERA_CAM5_LIT = 34,

    // Right Air Vent
    GG_CAMERA_CAM6_DARK = 39,
    GG_CAMERA_CAM6_LIT = 40,

    // Main Hall
    GG_CAMERA_CAM7_DARK = 52,
    GG_CAMERA_CAM7_LIT_DOOR_OPEN = 59,

    // Parts/Service
    GG_CAMERA_CAM8_DARK = 38,
    GG_CAMERA_CAM8_LIT_ALL = 19,
    GG_CAMERA_CAM8_LIT_CHICA_FREDDY = 201,
    GG_CAMERA_CAM8_LIT_FREDDY = 202,
    GG_CAMERA_CAM8_LIT = 203,
    GG_CAMERA_CAM8_LIT_FOXY = 209,

    // Show Stage
    GG_CAMERA_CAM9_DARK = 499,
    GG_CAMERA_CAM9_LIT = 499,

    // Game Area
    GG_CAMERA_CAM10_DARK = 323,
    GG_CAMERA_CAM10_LIT = 326,
    GG_CAMERA_CAM10_LIT_BB = 51,
    GG_CAMERA_CAM10_LIT_BB_FREDDY = 511,
    GG_CAMERA_CAM10_LIT_FREDDY = 514,

    // Prize Corner
    GG_CAMERA_CAM11_DARK = 77,
    GG_CAMERA_CAM11_LIT_P1 = 70,
    GG_CAMERA_CAM11_LIT_P2 = 72,
    GG_CAMERA_CAM11_LIT_P3 = 73,

    // Kid's Cove
    GG_CAMERA_CAM12_DARK = 78,
    GG_CAMERA_CAM12_LIT = 76,
    GG_CAMERA_CAM12_LIT_MANGLE = 82,

    GG_NO_ELEMENTS = 815
} game_graphic_t;

typedef enum game_font
{
    F_OCR_A,
    F_NO_ELEMENTS
} game_font_t;

typedef enum game_shader
{
    GS_PANORAMA,
    GS_NO_ELEMENTS
} game_shader_t;

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
