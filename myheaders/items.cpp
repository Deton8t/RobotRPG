#ifndef ITEMSCPP
#define ITEMSCPP
#include "sprite.cpp"
#include "graphics_helpers.cpp"
#include <string>
#include <vector>
#include "dialogue.cpp"
#include <SDL_ttf.h>


namespace items {
    namespace {
        struct attributes{
            int8_t hp,mp,atk,def,agi;
        };
        struct item {
            Sprite* sprite;
            std::string name;
            attributes base;
            int sprite_id;
        };
    }
    namespace inventory {
        bool is_active = false;
        std::vector<item> player_items = std::vector<item>();

        void toggle()
        {
            is_active = !is_active;
            if(is_active == true)
            {
                int i = 0;
                for(item _item : player_items)
                { 
                    SDL_Rect frame = {
                        (_item.sprite_id % 10) * 32,
                        (_item.sprite_id / 10) * 32,
                        32,
                        32
                    };
                    SDL_Rect pos = {20, 36*i, 32, 32}; 
                    graphics_helpers::texture_render(globals::item_sheet,frame,pos);
                    
                    i++;
                        
                }
            }
        }
    }

    void give(item _item) {
        inventory::player_items.push_back(_item);
    }

    // item_id used to render the sprite from one big item spritesheet
    void build_and_give(int item_sprite_id, std::string name, attributes _attributes) {
        give({nullptr, name, _attributes, item_sprite_id});
    }

};

#endif
