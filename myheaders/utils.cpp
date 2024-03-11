#include <SDL.h>
struct anim {
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
