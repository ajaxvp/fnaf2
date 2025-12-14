#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_ttf.h"
#include "SDL3/SDL_video.h"

#include "fnaf2.h"
#include "frame.h"
#include "log.h"
#include "graphics.h"

static runtime_properties_t properties = {
    .window_scale = 256
};

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static bool KEYS[SDL_SCANCODE_COUNT];

bool init(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        errorf("failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    if (!TTF_Init())
    {
        errorf("failed to initialize SDL font library: %s\n", SDL_GetError());
        return false;
    }

    SDL_CreateWindowAndRenderer("Five Nights at Freddy's 2",
        SCREEN_WIDTH_RATIO * properties.window_scale,
        SCREEN_HEIGHT_RATIO * properties.window_scale, 0, &window, &renderer);

    if (!window || !renderer)
    {
        errorf("could not create program window: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void cleanup(void)
{
    unload_all_graphics();
    unload_all_fonts();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_Quit();

    SDL_Quit();
}

int main(int argc, char** argv)
{
    int code = EXIT_SUCCESS;

    if (!init())
        return EXIT_FAILURE;

    bool quit = false;

    SDL_Event e;
    SDL_zero(e);

    game_state_t state = {0};

    game_frame_t* frame = frame_title();

    if (frame->init)
        frame->init(&state);

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_EVENT_QUIT:
                    quit = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (e.key.scancode >= SDL_SCANCODE_COUNT)
                    {
                        errorf("could not track key press event for key scancode %u\n", e.key.scancode);
                        break;
                    }
                    KEYS[e.key.scancode] = true;
                    break;
                case SDL_EVENT_KEY_UP:
                    if (e.key.scancode >= SDL_SCANCODE_COUNT)
                    {
                        errorf("could not track key release event for key scancode %u\n", e.key.scancode);
                        break;
                    }
                    KEYS[e.key.scancode] = false;
                    break;
            }
        }

        if (state.next_frame)
        {
            if (frame->deinit)
                frame->deinit(&state);
            frame = state.next_frame;
            if (frame->init)
                frame->init(&state);
            state.next_frame = NULL;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (frame->update)
            frame->update(&state);

        SDL_RenderPresent(renderer);
    }

    if (frame->deinit)
        frame->deinit(&state);

    cleanup();

    return code;
}

SDL_Renderer* get_renderer(void)
{
    return renderer;
}

runtime_properties_t* get_runtime_properties(void)
{
    return &properties;
}

bool is_key_pressed(SDL_Scancode code)
{
    if (code >= SDL_SCANCODE_COUNT)
    {
        errorf("could not get status of key with key scancode %u\n", code);
        return false;
    }
    return KEYS[code];
}
