#include <SDL.h>
#include <SDL_image.h>
#include <chrono>
#include <thread>
#include "SDL_render.h"
#include "myheaders/sprite.cpp"
int main()
{
    SDL_Init(SDL_INIT_EVERYTHING); 
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(1000, 800,0, &window, &renderer);
    bool game_is_running = true; 
    Animated_Sprite player = Animated_Sprite(renderer,"./acesprite/robodude.bmp", 32, 64, 20, 20);
    player.add_animation("run",1,4,10);
    player.start_animation("run",true);
    Clock clock;
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
                    }
            }
        }
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);
        player.update(renderer,clock);
        SDL_RenderPresent(renderer);
        clock.tick();
    }
    return 0;
}

