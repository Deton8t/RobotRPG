#ifndef BATTLE
#define BATTLE
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "./sprite.cpp"
#include "./globals.cpp"

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
        switch(party.size())
        {
            case 1:
                {
                    SDL_Rect* pos_rect = &party[0].a_sprite.current_sprite.position_rect;
                    pos_rect->x = SCREEN_WIDTH_PIXELS/2 - pos_rect->w/2; 
                    break;
                }
            case 2:
                std::cout << "hi \n";
                break;
        }
    }
};

#endif
