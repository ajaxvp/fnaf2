#include "SDL3/SDL_render.h"
#include "fnaf2.h"
#include "frame.h"
#include "graphics.h"

typedef enum camera
{
    C_PARTY_ROOM_1,
    C_PARTY_ROOM_2,
    C_PARTY_ROOM_3,
    C_PARTY_ROOM_4,
    C_LEFT_AIR_VENT,
    C_RIGHT_AIR_VENT,
    C_MAIN_HALL,
    C_PARTS_SERVICE,
    C_SHOW_STAGE,
    C_GAME_AREA,
    C_PRIZE_CORNER,
    C_KIDS_COVE,
    C_NO_ELEMENTS
} camera_t;

// TODO: initialize camera based on night
static camera_t cam = C_PRIZE_CORNER;

static SDL_Texture* get_camera_graphic(bool lit)
{
    game_graphic_t g = GG_CAMERA_CAM9_DARK;
    switch (cam)
    {
        case C_PARTY_ROOM_1:
            g = lit ? GG_CAMERA_CAM1_LIT : GG_CAMERA_CAM1_DARK;
            break;
        case C_PARTY_ROOM_2:
            g = lit ? GG_CAMERA_CAM2_LIT : GG_CAMERA_CAM2_DARK;
            break;
        case C_PARTY_ROOM_3:
            g = lit ? GG_CAMERA_CAM3_LIT : GG_CAMERA_CAM3_DARK;
            break;
        case C_PARTY_ROOM_4:
            g = lit ? GG_CAMERA_CAM4_LIT : GG_CAMERA_CAM4_DARK;
            break;
        case C_LEFT_AIR_VENT:
            g = lit ? GG_CAMERA_CAM5_LIT : GG_CAMERA_CAM5_DARK;
            break;
        case C_RIGHT_AIR_VENT:
            g = lit ? GG_CAMERA_CAM6_LIT : GG_CAMERA_CAM6_DARK;
            break;
        case C_MAIN_HALL:
            // TODO: fix
            g = lit ? GG_CAMERA_CAM7_LIT_DOOR_OPEN : GG_CAMERA_CAM7_DARK;
            break;
        case C_PARTS_SERVICE:
            g = lit ? GG_CAMERA_CAM8_LIT : GG_CAMERA_CAM8_DARK;
            break;
        case C_SHOW_STAGE:
            g = lit ? GG_CAMERA_CAM9_LIT : GG_CAMERA_CAM9_DARK;
            break;
        case C_GAME_AREA:
            g = lit ? GG_CAMERA_CAM10_LIT : GG_CAMERA_CAM10_DARK;
            break;
        case C_PRIZE_CORNER:
            // TODO: fix
            g = lit ? GG_CAMERA_CAM11_LIT_P1 : GG_CAMERA_CAM11_DARK;
            break;
        case C_KIDS_COVE:
            g = lit ? GG_CAMERA_CAM12_LIT : GG_CAMERA_CAM12_DARK;
            break;
        default:
            return NULL;
    }
    return get_graphic(g);
}

static int init(game_state_t* state, void* message)
{
    // texture initializations
    return 0;
}

static int update(game_state_t* state)
{
    SDL_Texture* cg = get_camera_graphic(is_key_pressed(SDL_SCANCODE_LCTRL));
    SDL_FRect cg_loc = {
        .x = 0,
        .y = 0,
        .w = cg->w,
        .h = cg->h
    };
    SDL_RenderTexture(get_renderer(), cg, NULL, &cg_loc);
    return 0;
}

static int deinit(game_state_t* state)
{
    // texture deinits
    return 0;
}

static game_frame_t frame = {
    GF_CAMERA,
    init,
    update,
    deinit
};

game_frame_t* frame_camera(void)
{
    return &frame;
}
