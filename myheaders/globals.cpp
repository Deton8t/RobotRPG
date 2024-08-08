#ifndef GLOBALS
#define GLOBALS

#include "SDL_render.h"
#include <SDL.h>
#include "SDL_mixer.h"
#include <string>
#include "macros.cpp"

#include "player.cpp"
#define GLOBAL_TSPRITE_SIZE 32

#define STATE_NORMAL 0
#define STATE_INVENTORY 1

namespace globals {

    SDL_Renderer* renderer;
    std::string game_state;
    Player* player;
    Clock* clock;
    SDL_Texture* item_sheet;
    Mix_Music* current_song;

};

#endif
