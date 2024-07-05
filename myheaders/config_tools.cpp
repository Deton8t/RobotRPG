#ifndef CONFIG_TOOLS
#define CONFIG_TOOLS

#include <SDL.h>
#include "./player.cpp"

// Keep the settings for building your player here maybe read from a config file(?)
void build_player(Player &player, SDL_Renderer* renderer)
{
    player.init_sprite(renderer,"./acesprite/robodude.bmp", 32,32,20,20);
    player.animated_sprite.add_animation("run",1,4,10);
    player.animated_sprite.add_animation("idle",0,0,10);
}

#endif
