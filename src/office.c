#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "fnaf2.h"
#include "frame.h"
#include "graphics.h"

typedef enum game_animation_type
{
    ANIM_CAMERA_FLIP
} game_animation_type_t;

static game_graphic_t DESK_GRAPHICS[] = {
    GG_OFFICE_DESK_F1,
    GG_OFFICE_DESK_F2,
    GG_OFFICE_DESK_F3,
    GG_OFFICE_DESK_F4
};

static game_graphic_t CAMERA_FLIP_ANIMATION_FRAMES[] = {
    GG_CAMERA_FLIP_F1,
    GG_CAMERA_FLIP_F2,
    GG_CAMERA_FLIP_F3,
    GG_CAMERA_FLIP_F4,
    GG_CAMERA_FLIP_F5,
    GG_CAMERA_FLIP_F6,
    GG_CAMERA_FLIP_F7,
    GG_CAMERA_FLIP_F8,
    GG_CAMERA_FLIP_F9,
    GG_CAMERA_FLIP_F10
};

static int camera_finish(game_state_t* state)
{
    change_frame(state, frame_camera(), NULL);
    return 0;
}

static int init(game_state_t* state, void* message)
{
    // texture initializations
    return 0;
}

static int update(game_state_t* state)
{
    static int pos = 0;

    static SDL_FRect move_left = {
        .x = 0,
        .y = 0,
        .w = 240,
        .h = 768
    };

    static SDL_FRect move_right = {
        .x = 1024 - 240,
        .y = 0,
        .w = 240,
        .h = 768
    };

    runtime_properties_t* properties = get_runtime_properties();
    SDL_Renderer* r = get_renderer();

    SDL_Texture* office = get_graphic(GG_OFFICE_NORMAL);

    SDL_FRect office_dim = {
        .x = -(int) ((office->w - (SCREEN_WIDTH_RATIO * properties->window_scale)) / 2) + pos,
        .y = 0,
        .w = office->w,
        .h = office->h
    };

    if (is_key_pressed(SDL_SCANCODE_LCTRL))
        office = get_graphic(GG_OFFICE_FRONT_LIGHT);

    SDL_RenderTexture(r, office, NULL, &office_dim);

    SDL_Texture* desk = get_graphic(DESK_GRAPHICS[(SDL_GetTicks() / 10) % (sizeof(DESK_GRAPHICS) / sizeof(DESK_GRAPHICS[0]))]);
    SDL_FRect desk_dim = {
        .x = pos + 150,
        .y = (SCREEN_HEIGHT_RATIO * properties->window_scale) - desk->h,
        .w = desk->w,
        .h = desk->h
    };
    SDL_RenderTexture(r, desk, NULL, &desk_dim);

    SDL_FRect mask_flipper_loc = {0};
    render_texture(25, 700, get_graphic(GG_MASK_FLIPPER), &mask_flipper_loc);

    SDL_FRect camera_flipper_loc = {0};
    render_texture(512, 700, get_graphic(GG_CAMERA_FLIPPER), &camera_flipper_loc);
    if (mouse_in_frect(&camera_flipper_loc) && !is_animation_active(state, ANIM_CAMERA_FLIP))
    {
        static game_animation_t anim = {
            .id = ANIM_CAMERA_FLIP,
            .x = 0,
            .y = 0,
            .interval = 20,
            .frames = CAMERA_FLIP_ANIMATION_FRAMES,
            .frame_count = sizeof(CAMERA_FLIP_ANIMATION_FRAMES) / sizeof(CAMERA_FLIP_ANIMATION_FRAMES[0]),
            .finish = camera_finish
        };
        start_animation(state, &anim);
    }

    if (mouse_in_frect(&move_left) && pos < 800 - 512) pos += 1;
    if (mouse_in_frect(&move_right) && pos > -800 + 512) pos -= 1;

    render_animation(state, ANIM_CAMERA_FLIP);

    return 0;
}

static int deinit(game_state_t* state)
{
    // texture deinits
    return 0;
}

static game_frame_t frame = {
    GF_OFFICE,
    init,
    update,
    deinit
};

game_frame_t* frame_office(void)
{
    return &frame;
}
