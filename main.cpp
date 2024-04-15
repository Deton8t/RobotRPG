#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "SDL_render.h"
#include "./myheaders/utils.cpp"
#include "./myheaders/player.cpp"
#include "./myheaders/stage.cpp"
#include "./myheaders/config_tools.cpp"
#include "./myheaders/music.cpp"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING); 
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(1024, 640 ,0, &window, &renderer);
    bool game_is_running = true;
    Player player;
    build_player(player,renderer);
    Clock clock;
    music::init_music();
    music::play_music("ForJaden.mp3",false);
    while(game_is_running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)) 
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    {
                        game_is_running = false;
                        break;
                    }
                case SDL_KEYDOWN:
                    {
                        player.handle_keydown(event.key.keysym.scancode);
                        break;
                    }
                case SDL_KEYUP:
                    {
                        player.handle_keyup(event.key.keysym.scancode);
                        break;
                    }

            }
        }
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);
        player.update_sprite(renderer,clock);
        SDL_RenderPresent(renderer);
        clock.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

    }
    return 0;
}

