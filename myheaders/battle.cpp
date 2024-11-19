#ifndef BATTLE
#define BATTLE
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "./sprite.cpp"
#include "./globals.cpp"
#include "./menus.cpp"
#include "SDL_events.h"
#include "SDL_render.h"
#include "macros.cpp"

enum move_type {
    ELECTRIC_ATTACK,
};

struct move {
    move_type type;
    int low,high; // Damage/Buff/Heal/etc. Output range
    std::string desc;
};

struct enemy
{
    std::string desc;
    std::vector<move> moves;
    Animated_Sprite a_sprite;
    float hp;
};

struct party_member
{
    std::string desc;
    std::vector<move> moves;
    Animated_Sprite a_sprite;
    float hp;
};
namespace battle
{
    std::vector<enemy> enemies;
    std::vector<party_member> party;
    void render_enemies(){
        switch(enemies.size())
        {
            case 1:
                {
                SDL_Rect* pos_rect = &enemies[0].a_sprite.current_sprite.position_rect;
                pos_rect->x = SCREEN_WIDTH_PIXELS/2 - pos_rect->w/2; 
                pos_rect->y = SCREEN_HEIGHT_PIXELS/3;
                break;
                }
            case 2:
                std::cout << "hi \n";
                break;
        }
    }
    void render_party(){
        SDL_Rect temp_rect = {0,SCREEN_HEIGHT_PIXELS/3*2,SCREEN_WIDTH_PIXELS, SCREEN_HEIGHT_PIXELS/3};
        SDL_SetRenderDrawColor(globals::renderer,100,0,100,255);
        
        menus::render_ui_box(temp_rect.x,temp_rect.y,temp_rect.w,temp_rect.h);
        switch(party.size())
        {
            case 1:
                {
                    SDL_Rect* pos_rect = &party[0].a_sprite.current_sprite.position_rect;
                    pos_rect->w*=2;
                    pos_rect->h*=2;
                    pos_rect->x = SCREEN_WIDTH_PIXELS/2 - pos_rect->w/2; 
                    pos_rect->y = SCREEN_HEIGHT_PIXELS/3 * 2;
                    menus::render_ui_box(pos_rect->x,pos_rect->y+34,pos_rect->w,pos_rect->h-30);
                    SDL_SetRenderDrawColor(globals::renderer,150,0,100, 255);
                    party[0].a_sprite.current_sprite.load_sprite(globals::renderer,false);
                    break;
                }
            default:
                std::cout << "hi \n";
                break;
        }
    }

    void update(SDL_Event* event) {
        menus::display_text({0,0,400,400}, "BATTLE", 40);
        party.clear();
        party_member dummy = {"hi",std::vector<move>(), Animated_Sprite(globals::player->animated_sprite), 10};
        party.push_back(dummy);
        render_party();

    }
};

#endif
