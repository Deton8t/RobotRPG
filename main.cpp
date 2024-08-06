#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <thread>
#include "SDL_render.h"

#include "./myheaders/utils.cpp"
#include "./myheaders/player.cpp"
#include "./myheaders/config_tools.cpp"
#include "./myheaders/music.cpp"
#include "./myheaders/stage.cpp"
#include "./myheaders/globals.cpp"
#include "./myheaders/dialogue.cpp"
#include "./myheaders/font.cpp"
#include "./myheaders/graphics_helpers.cpp"
#include "./myheaders/state.cpp"
#include "./myheaders/menus.cpp"
#include "./myheaders/items.cpp"
#include "./myheaders/party.cpp"
#include "./myheaders/save_load.cpp"
#include "./myheaders/inventory.cpp"
#define SCREEN_W 1024
#define SCREEN_H 640




int main() 
{
    SDL_Init(SDL_INIT_EVERYTHING); 
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
    bool game_is_running = true;
    Player player;
    build_player(player,renderer);
    Clock clock;
    music::init_music();
    stage::init(renderer);
    font::init();
    globals::renderer = renderer;
    globals::player = &player;
    globals::clock = &clock;
    globals::item_sheet = SDL_CreateTextureFromSurface(renderer, IMG_Load("./images/sprites/item_sheets.png"));
    stage::set(stage_names::TEST);
    party::start();
    load::items();
    uint8_t state = STATE_NORMAL;
    while(game_is_running)
    {
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);

        SDL_Event event;
        if (state == STATE_NORMAL) {
            while(SDL_PollEvent(&event)) 
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                        {
                            game_is_running = false;
                            save::items();
                            save::party();
                            save::stage();
                            break;
                        }
                    case SDL_KEYDOWN:
                        {
                            player.handle_keydown(event.key.keysym.scancode);
                            if(event.key.keysym.scancode == SDL_SCANCODE_R) {
                                stage::set(stage_names::RANDOM);
                            }
                            if(event.key.keysym.scancode == SDL_SCANCODE_I && dialogue::is_on() == false) {
                                state = STATE_INVENTORY;
                                  //std::string name = "item ";
                                  //name += std::to_string(inventory::player_items.size());
                                  //std::vector<i_stat> stats = std::vector<i_stat>();
                                  //stats.push_back({"atk",0,11});
                                  //stats.push_back({"def",0,int8_t(rand()%20)});
                                  //stats.push_back({"wis",0,int8_t(rand()%20)});
                                  //stats.push_back({"agi",0,int8_t(rand()%20)});
                                  //stats.push_back({"man",0,int8_t(rand()%20)});
                                  //stats.push_back({"hea",0,int8_t(rand()%20)});
                                  //inventory::give({nullptr,name,stats,rand()%4,static_cast<item_type>(rand()%4)});
                                }
                            break;
                        }
                    case SDL_KEYUP:
                        {
                            player.handle_keyup(event.key.keysym.scancode);
                            break;
                        }

                }
            }
        }
        stage::update();
        player.update_sprite(renderer,clock);
        if(state == STATE_INVENTORY) {
            player.pause();
            inventory::toggle();            
            inventory::preview();
            inventory::show_character(); 
            while(SDL_PollEvent(&event)) 
           {
                switch(event.type)
                {
                    case SDL_QUIT:
                        {
                            game_is_running = false;
                            save::items();
                            break;
                        }
                    case SDL_KEYDOWN:
                        {
                            state::in_inventory::handle_keydown(event.key.keysym.scancode,&state);
                            break;
                        }
                }

            }
        }
        SDL_RenderPresent(renderer);
        clock.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

    }
    return 0;
}
