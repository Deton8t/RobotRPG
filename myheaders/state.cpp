#ifndef STATE_CPP 
#define STATE_CPP 

#include "SDL.h"
#include "globals.cpp"
#include "items.cpp"
#include "inventory.cpp"
#include "party.cpp"
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
                    inventory::next();
                    break;
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_K:
                    inventory::back();
                    break;
                case SDL_SCANCODE_E:
                    party::equip(&party::party[inventory::party_index],inventory::current());
                default:
                    break;
            }
        };
    }
};

#endif
