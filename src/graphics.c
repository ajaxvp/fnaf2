#include "SDL3/SDL_iostream.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_image.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_ttf.h"
#include "frame.h"
#include "graphics.h"
#include "fnaf2.h"
#include "log.h"

#define MAX_FILEPATH 512

static SDL_Texture* GAME_GRAPHICS[GG_NO_ELEMENTS];

static TTF_Font* FONTS[F_NO_ELEMENTS][FS_NO_ELEMENTS];

static const char* FONT_LOCATIONS[] = {
    [F_OCR_A] = "resources/font/ocr_a.ttf"
};

static float FONT_SIZE_VALUES[] = {
    [FS_SMALL] = 8.0f,
    [FS_MEDIUM] = 16.0f,
    [FS_LARGE] = 24.0f,
    [FS_TITLE] = 40.0f
};

TTF_Font* get_font(game_font_t font, font_size_t size)
{
    if (FONTS[font][size])
        return FONTS[font][size];

    return FONTS[font][size] = TTF_OpenFontIO(SDL_IOFromFile(FONT_LOCATIONS[font], "r"),
        true, (FONT_SIZE_VALUES[size] * get_runtime_properties()->window_scale) / 256);
}

bool unload_font(game_font_t font, font_size_t size)
{
    if (!FONTS[font][size])
        return false;

    TTF_CloseFont(FONTS[font][size]);
    FONTS[font][size] = NULL;
    return true;
}

void unload_all_fonts(void)
{
    for (size_t font = 0; font < F_NO_ELEMENTS; ++font)
        for (size_t size = 0; size < FS_NO_ELEMENTS; ++size)
            unload_font(font, size);
}

SDL_Texture* get_graphic(game_graphic_t g)
{
    if (GAME_GRAPHICS[g])
        return GAME_GRAPHICS[g];
    char filepath[MAX_FILEPATH];
    snprintf(filepath, sizeof(filepath), "resources/img/%d.png", g);
    SDL_Surface* surface = IMG_Load(filepath);
    SDL_Texture* img = SDL_CreateTextureFromSurface(get_renderer(), surface);
    SDL_DestroySurface(surface);
    return GAME_GRAPHICS[g] = img;
}

bool unload_graphic(game_graphic_t g)
{
    if (!GAME_GRAPHICS[g])
        return false;
    SDL_DestroyTexture(GAME_GRAPHICS[g]);
    GAME_GRAPHICS[g] = NULL;
    return true;
}

void unload_all_graphics(void)
{
    for (size_t i = 0; i < GG_NO_ELEMENTS; ++i)
        unload_graphic(i);
}

game_animation_t* start_animation(game_state_t* state, game_animation_t* anim)
{
    if (anim->id >= MAX_ANIMATIONS)
    {
        errorf("animation ID is outside of allowed range (0-%d)\n", MAX_ANIMATIONS - 1);
        return NULL;
    }
    state->animations[anim->id] = *anim;
    game_animation_t* a = &state->animations[anim->id];
    a->active_frame = 0;
    a->start = SDL_GetTicks();
    return a;
}

bool is_animation_active(game_state_t* state, uint32_t id)
{
    if (id >= MAX_ANIMATIONS)
        return false;
    return state->animations[id].frames;
}

bool render_animation(game_state_t* state, uint32_t id)
{
    if (id >= MAX_ANIMATIONS)
        return false;
    game_animation_t* anim = &state->animations[id];
    if (!is_animation_active(state, id))
        return false;
    render_texture(anim->x, anim->y, get_graphic(anim->frames[anim->active_frame]), NULL);
    uint64_t ticks = SDL_GetTicks();
    if (ticks >= anim->start + anim->interval)
    {
        anim->start = ticks;
        ++anim->active_frame;
        if (anim->active_frame >= anim->frame_count)
        {
            anim->frames = NULL;
            anim->finish(state);
        }
    }
    return true;
}
