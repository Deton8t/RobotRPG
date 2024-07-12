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
#include <sys/_types/_u_int8_t.h>
#include <vector>
#include <format>
#include "dialogue.cpp"
#include <SDL_ttf.h>


namespace items {
    namespace {
        struct attributes{
            int8_t hp,mp,atk,def,agi;
        };
        struct stat {
            std::string name;
            bool percentage;
            int8_t value;
        };
        struct item {
            Sprite* sprite;
            std::string name;
            std::vector<stat> stats;
            int sprite_id;
        };
    }
        typedef enum {
            MAIN,
            PREVIEW,
            EQUIP
        } INV_State;

    namespace inventory {
        INV_State inv_state;
        u_int8_t index = 0;
        std::vector<item> player_items = std::vector<item>();
        
        void next() {
            index++;
            if(index >= player_items.size())
                index = 0;
        }

        void back() {
            index--;
            if(index == 255)
                index = player_items.size() - 1;
        }

        void toggle()
        {
            menus::render_ui_box(10,5,SCREEN_WIDTH_PIXELS/2-10,39*15);
            std::string inventory_text = "Inventory ( ";
            inventory_text += std::to_string(player_items.size());
            inventory_text += " /200)";
            menus::display_text(SDL_Rect({22,10,0,32}),inventory_text);
            int offset = std::max(index-14,0);
            std::cout << offset << "\n";
            for(int i = 0; i < std::min((int)player_items.size(),15); i++)
            { 
                item _item = player_items[i+offset];
                SDL_Rect frame = {
                    (_item.sprite_id % 10) * 16,
                    (_item.sprite_id / 10) * 16,
                    16,
                    16
                };
                SDL_Rect pos = {20, 10 + 36 + 36*i, 32, 32}; 
                if(i+offset == index) {
                    pos.y += 5;
                    menus::display_text(pos, "-");
                    pos.y -= 5;
                    pos.x += 20;
                }
                graphics_helpers::texture_render(globals::item_sheet,frame,pos);
                pos.x += 38;
                pos.y += 3;
                menus::display_text(pos,_item.name);

            }
        }
        void preview() {
            item* current = &player_items[index];
            menus::render_ui_box(SCREEN_WIDTH_PIXELS/2+10, 5, SCREEN_WIDTH_PIXELS/2-20, 39*15/2);
            SDL_Rect name_box = {(SCREEN_WIDTH_PIXELS/4) * 3 - ((int)current->name.size()/2*20),
                                20, 
                                0,
                                0};
            menus::display_text(name_box,current->name,20);
            SDL_Rect stat_table_box = SDL_Rect();
            // I luv u jaden <3
            std::vector<stat>* current_s = &current->stats; 
            for(int i = 0; i < current_s->size(); i++)
            {
                u_int8_t col = i / 4;
                u_int8_t row = i % 4;
                stat_table_box.x = SCREEN_WIDTH_PIXELS/2+20 + (col * SCREEN_WIDTH_PIXELS/8 + 16);
                stat_table_box.y = 60 + row *42;
                menus::display_text(stat_table_box, current_s->at(i).name + " " + std::to_string(current_s->at(i).value) );
            }
            menus::display_text({SCREEN_WIDTH_PIXELS/2+36, SCREEN_HEIGHT_PIXELS/2 - 64, 0,0}, "(E)quip (C)ompare");

        }

    }

    void give(item _item) {
        inventory::player_items.push_back(_item);
    }

    // item_id used to render the sprite from one big item spritesheet
    void build_and_give(int item_sprite_id, std::string name, std::vector<stat> stats) {
        give({nullptr, name, stats, item_sprite_id});
    }

};

#endif
