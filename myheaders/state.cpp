#ifndef STATE_CPP 
#define STATE_CPP 

#include "SDL.h"
#include "globals.cpp"
#include <cstdint>
namespace state_funcs {
    void handle_keydown(SDL_Scancode key, uint8_t* state) {
        switch(key) {
            case SDL_SCANCODE_ESCAPE:
                *state = STATE_NORMAL;
            default:
                break;
        }
    }
};

#endif
