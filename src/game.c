#include "SDL3/SDL_timer.h"
#include <stdint.h>
#include <stdlib.h>

#define NO_ANIMATRONICS 11

typedef enum animatronic_location
{
    AL_PARTY_ROOM_1,
    AL_PARTY_ROOM_2,
    AL_PARTY_ROOM_3,
    AL_PARTY_ROOM_4,
    AL_LEFT_AIR_VENT,
    AL_RIGHT_AIR_VENT,
    AL_MAIN_HALL,
    AL_PARTS_SERVICE,
    AL_SHOW_STAGE,
    AL_GAME_AREA,
    AL_PRIZE_CORNER,
    AL_KIDS_COVE,
    AL_OFFICE,
    AL_NO_ELEMENTS
} animatronic_location_t;

typedef enum animatronic_id
{
    AID_TOY_FREDDY,
    AID_TOY_BONNIE,
    AID_TOY_CHICA,
    AID_MANGLE,
    AID_BB,
    AID_MARIONETTE,
    AID_WITHERED_FREDDY,
    AID_WITHERED_BONNIE,
    AID_WITHERED_CHICA,
    AID_WITHERED_FOXY,
    AID_WITHERED_GOLDEN_FREDDY
} animatronic_id_t;

typedef struct animatronic
{
    animatronic_id_t id;
    animatronic_location_t location;
    uint32_t ai_level;
    uint64_t next_opportunity;
} animatronic_t;

static animatronic_t ANIMATRONICS[NO_ANIMATRONICS] = {
    {
        .id = AID_TOY_FREDDY,
        .location = AL_SHOW_STAGE
    },
    {
        .id = AID_TOY_BONNIE,
        .location = AL_SHOW_STAGE
    },
    {
        .id = AID_TOY_CHICA,
        .location = AL_SHOW_STAGE
    },
    {
        .id = AID_MANGLE,
        .location = AL_KIDS_COVE
    },
    {
        .id = AID_BB,
        .location = AL_GAME_AREA
    },
    {
        .id = AID_MARIONETTE,
        .location = AL_PRIZE_CORNER
    },
    {
        .id = AID_WITHERED_FREDDY,
        .location = AL_PARTS_SERVICE
    },
    {
        .id = AID_WITHERED_BONNIE,
        .location = AL_PARTS_SERVICE
    },
    {
        .id = AID_WITHERED_CHICA,
        .location = AL_PARTS_SERVICE
    },
    {
        .id = AID_WITHERED_FOXY,
        .location = AL_PARTS_SERVICE
    },
    {
        .id = AID_WITHERED_GOLDEN_FREDDY,
        .location = AL_PARTS_SERVICE
    }
};

void set_ai_level(animatronic_id_t id, uint32_t level)
{
    ANIMATRONICS[id].ai_level = level;
}

void set_all_ai_levels(uint32_t levels[NO_ANIMATRONICS])
{
    for (size_t i = 0; i < sizeof(ANIMATRONICS) / sizeof(ANIMATRONICS[0]); ++i)
        ANIMATRONICS[i].ai_level = levels[i];
}

void initialize_animatronic_opportunities(void)
{
    uint64_t o = SDL_GetTicks() + 5000;
    for (size_t i = 0; i < sizeof(ANIMATRONICS) / sizeof(ANIMATRONICS[0]); ++i)
        ANIMATRONICS[i].next_opportunity = o;
}

void force_move_animatronic(animatronic_id_t id, animatronic_location_t loc)
{
    ANIMATRONICS[id].location = loc;
}

bool try_move_animatronic(animatronic_id_t id, animatronic_location_t loc)
{
    animatronic_t* a = &ANIMATRONICS[id];
    if (SDL_GetTicks() < a->next_opportunity)
        return false;
    a->next_opportunity += 5000;
    if (a->ai_level >= (rand() % 20) + 1)
    {
        ANIMATRONICS[id].location = loc;
        return true;
    }
    return false;
}
