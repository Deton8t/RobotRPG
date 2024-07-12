#ifndef STATE_CPP 
#define STATE_CPP 

#include "SDL.h"
#include "globals.cpp"
#include "items.cpp"
#include <cstdint>
namespace state {
    namespace in_inventory {
        void handle_keydown(SDL_Scancode key, uint8_t* state) {
            switch(key) {
                case SDL_SCANCODE_ESCAPE:
                    *state = STATE_NORMAL;
                    break;
                case SDL_SCANCODE_DOWN:
                case SDL_SCANCODE_J:
                    items::inventory::next();
                    break;
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_K:
                    items::inventory::back();
                    break;
                default:
                    break;
            }
        };
    }
};

#endif
