#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_ttf.h"
#include "frame.h"
#include "graphics.h"
#include "fnaf2.h"
#include "log.h"

const SDL_Color WHITE = {
    0xFF,
    0xFF,
    0xFF,
    0x00
};

static const game_graphic_t STATIC_GRAPHICS[] = {
    GG_STATIC_F1,
    GG_STATIC_F2,
    GG_STATIC_F3,
    GG_STATIC_F4,
    GG_STATIC_F5,
    GG_STATIC_F6
};

#define NO_STATIC_GRAPHICS sizeof(STATIC_GRAPHICS) / sizeof(STATIC_GRAPHICS[0])

typedef enum title_texture
{
    T_FIVE,
    T_NIGHTS,
    T_AT,
    T_FREDDYS,
    T_TWO,
    T_NEW_GAME,
    T_CONTINUE,
    T_ARROW,
    NO_TEXTURES    
} title_texture_t;

static SDL_Texture* TEXTURES[NO_TEXTURES];

SDL_Texture* create_text_texture(const char* text, game_font_t font, font_size_t size, const SDL_Color* color)
{
    SDL_Renderer* r = get_renderer();
    TTF_Font* f = get_font(font, size);
    SDL_Surface* surface = TTF_RenderText_Blended(f, text, 0, *color);
    SDL_Texture* t = SDL_CreateTextureFromSurface(r, surface);
    SDL_DestroySurface(surface);
    return t;
}

bool mouse_clicked(void)
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK;
}

static int init(game_state_t* state, void* message)
{
    TEXTURES[T_FIVE] = create_text_texture("Five", F_OCR_A, FS_TITLE, &WHITE);
    TEXTURES[T_NIGHTS] = create_text_texture("Nights", F_OCR_A, FS_TITLE, &WHITE);
    TEXTURES[T_AT] = create_text_texture("at", F_OCR_A, FS_TITLE, &WHITE);
    TEXTURES[T_FREDDYS] = create_text_texture("Freddy's", F_OCR_A, FS_TITLE, &WHITE);
    TEXTURES[T_TWO] = create_text_texture("2", F_OCR_A, FS_TITLE, &WHITE);
    TEXTURES[T_NEW_GAME] = create_text_texture("New Game", F_OCR_A, FS_TITLE, &WHITE);
    TEXTURES[T_CONTINUE] = create_text_texture("Continue", F_OCR_A, FS_TITLE, &WHITE);
    TEXTURES[T_ARROW] = create_text_texture(">>", F_OCR_A, FS_TITLE, &WHITE);
    return 0;
}

static int update(game_state_t* state)
{
    SDL_Renderer* r = get_renderer();

    SDL_RenderTexture(r, get_graphic(GG_TITLE_BG_NORMAL), NULL, NULL);
    SDL_Texture* static_texture = get_graphic(STATIC_GRAPHICS[(SDL_GetTicks() / 5) % NO_STATIC_GRAPHICS]);
    SDL_RenderTexture(r, static_texture, NULL, NULL);

    static const float title_x_align = 75.0f;
    static const float indicator_align = 15.0f;

    render_texture(title_x_align, 100, TEXTURES[T_FIVE], NULL);
    render_texture(title_x_align, 150, TEXTURES[T_NIGHTS], NULL);
    render_texture(title_x_align, 200, TEXTURES[T_AT], NULL);
    render_texture(title_x_align, 250, TEXTURES[T_FREDDYS], NULL);
    render_texture(title_x_align, 300, TEXTURES[T_TWO], NULL);

    SDL_FRect new_game_loc = {0};
    render_texture(title_x_align, 400, TEXTURES[T_NEW_GAME], &new_game_loc);

    if (mouse_in_frect(&new_game_loc))
    {
        render_texture(indicator_align, 400, TEXTURES[T_ARROW], NULL);
        if (mouse_clicked())
        {
            change_frame(state, frame_office(), NULL);
            return 0;
        }
    }

    SDL_FRect continue_loc = {0};
    render_texture(title_x_align, 475, TEXTURES[T_CONTINUE], &continue_loc);

    if (mouse_in_frect(&continue_loc))
    {
        render_texture(indicator_align, 475, TEXTURES[T_ARROW], NULL);
        if (mouse_clicked())
            infof("Continue clicked\n");
    }

    return 0;
}

static int deinit(game_state_t* state)
{
    for (size_t i = 0; i < NO_TEXTURES; ++i)
        SDL_DestroyTexture(TEXTURES[i]);

    return 0;
}

static game_frame_t frame = {
    GF_TITLE,
    init,
    update,
    deinit
};

game_frame_t* frame_title(void)
{
    return &frame;
}
