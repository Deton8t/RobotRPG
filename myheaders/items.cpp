#ifndef ITEMSCPP
#define ITEMSCPP
#include "globals.cpp"
#include "sprite.cpp"
#include "graphics_helpers.cpp"
#include "./menus.cpp"
#include <cstdint>
#include <format>
#include <iostream>
#include <string>
#include <strings.h>
#include <sys/_types/_u_int8_t.h>
#include <vector>
#include <format>
#include "dialogue.cpp"
#include <SDL_ttf.h>


namespace items {
         enum item_type {
            head,
            chest,
            legs,
            boots,
            weapon,
        };

        struct i_stat {
            std::string name;
            bool is_percentage;
            int8_t value;
        };
        struct item {
            Sprite* sprite;
            std::string name;
            std::vector<i_stat> stats;
            int sprite_id;
            item_type type;
            u_int8_t index;
        };
    };

#endif
