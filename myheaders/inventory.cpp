#ifndef INVENTORYCPP
#define INVENTORYCPP
#include "globals.cpp"
#include "items.cpp"
#include <vector>
#include "character.cpp"
#include "party.cpp"

typedef enum {
    MAIN,
    PREVIEW,
    EQUIP
} INV_State;

using namespace items;
namespace inventory {
    INV_State inv_state;
    u_int8_t index = 0;
    u_int8_t party_index = 0;
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
        std::vector<i_stat>* current_s = &current->stats; 
        for(int i = 0; i < current_s->size(); i++)
        {
            u_int8_t col = i / 2;
            u_int8_t row = i % 2;
            stat_table_box.x = SCREEN_WIDTH_PIXELS/2+70 + (col * SCREEN_WIDTH_PIXELS/8 + 16);
            stat_table_box.y = 100 + row *42;
            menus::display_text(stat_table_box, current_s->at(i).name + " " + std::to_string(current_s->at(i).value) );
        }
        menus::display_text({SCREEN_WIDTH_PIXELS/2+(16*8), SCREEN_HEIGHT_PIXELS/2 - 70, 0,0}, "(E)quip (C)ompare");
    }

    void show_character() {
        SDL_Rect outer = menus::render_ui_box(SCREEN_WIDTH_PIXELS/2+10,SCREEN_HEIGHT_PIXELS/2-20,SCREEN_WIDTH_PIXELS/2-20,SCREEN_HEIGHT_PIXELS/2-30);
        character::character* current = &party::party[party_index];
        menus::display_text(
                {
                outer.x + outer.w/2 - ((int)current->name.size()/2)*20,
                outer.y+5,
                0,
                0
                }, 
                current->name,
                20
                );        
        int i = 0;
        SDL_Rect table_rect = outer; 
        for(auto& [key,value] : current->total_stats) {
            u_int8_t col = i / 2;
            u_int8_t row = i % 2;
            table_rect.x = outer.x+70 + (col * outer.w/3 - 30);
            table_rect.y = outer.y + 60 + row *42;
            menus::display_text(table_rect, key + " " + std::to_string(value.get()));
            i++;
        }
        table_rect.x = outer.x + 15;
        table_rect.y = outer.y + 140;
        menus::display_text(table_rect, "  HEAD:",12);
        table_rect.y += 28;
        menus::display_text(table_rect, " CHEST:",12);
        table_rect.y += 28;
        menus::display_text(table_rect, "  LEGS:",12);
        table_rect.y += 28;
        menus::display_text(table_rect, " BOOTS:",12);
        table_rect.y += 28;
        menus::display_text(table_rect, "WEAPON:",12);
        current->equips[4] = &player_items[0];
        table_rect.x = outer.x + 15 + 12*8;
        table_rect.y = outer.y + 140;
        for(int i = 0; i < current->equips.size(); i++) 
        {
            if(current->equips[i] != nullptr)
            {
                menus::display_text(table_rect, current->equips[i]->name, 12 );
            }
            table_rect.y += 28;
        }

    }

    item* current()
    {
        return &player_items[index];
    }

    void give(item _item) {
        _item.index = (int)inventory::player_items.size();
        inventory::player_items.push_back(_item);
    }

    void remove(u_int8_t index) {
        for (u_int8_t i = inventory::player_items.size()-1; i > index; i--) {
            inventory::player_items[i].index--;
        }
        inventory::player_items.erase(inventory::player_items.cbegin()+index);

    }

    // item_id used to render the sprite from one big item spritesheet
    void build_and_give(int item_sprite_id, std::string name, std::vector<i_stat> stats) {
        give({nullptr, name, stats, item_sprite_id});
    }

}
#endif
