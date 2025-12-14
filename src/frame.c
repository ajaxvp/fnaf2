#include "frame.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "fnaf2.h"

inline void change_frame(game_state_t* state, game_frame_t* frame, void* message)
{
    state->next_frame = frame;
    state->message = message;
}

bool mouse_in_frect(SDL_FRect* frect)
{
    float mx = 0.0f, my = 0.0f;
    SDL_GetMouseState(&mx, &my);
    return mx >= frect->x && mx <= frect->x + frect->w && my >= frect->y && my <= frect->y + frect->h;
}

void render_texture(float x, float y, SDL_Texture* texture, SDL_FRect* loc)
{
    runtime_properties_t* properties = get_runtime_properties();
    SDL_FRect l = {
        .x = x,
        .y = y,
        .w = ((float) texture->w * properties->window_scale) / 256,
        .h = ((float) texture->h * properties->window_scale) / 256
    };
    if (loc)
        *loc = l;
    SDL_RenderTexture(get_renderer(), texture, NULL, &l);
}
