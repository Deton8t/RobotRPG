#ifndef UTILS
#define UTILS
#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include <string>

struct Point2D
{
    int x,y;	
};

struct Anim {
    int start;
    int end;
    int frame_rate;
};

struct Clock {
    u_int32_t last_tick_time = 0;
    u_int32_t delta_ms = 0;

    void tick()
    {
        u_int32_t current_tick = SDL_GetTicks64();
        delta_ms = current_tick - last_tick_time;
        last_tick_time = current_tick;
    }
};
bool is_colliding(SDL_Rect a, SDL_Rect b)
{
    if(
            a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y
      )
    {
        return true;
    }
    return false;
}

#endif
