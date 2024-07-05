#ifndef PLAYER
#define PLAYER
#include <SDL.h>
#include "SDL_rect.h"
#include "SDL_render.h"
#include "sprite.cpp"
#include <cstdint>
#include <iostream>
#include <map>

#define PLAYER_SIZE 3

struct Bindings {
    SDL_Scancode forwards = SDL_SCANCODE_W;
    SDL_Scancode backwards = SDL_SCANCODE_S;
    SDL_Scancode left = SDL_SCANCODE_A;
    SDL_Scancode right = SDL_SCANCODE_D;
    SDL_Scancode sprint = SDL_SCANCODE_LSHIFT;
    SDL_Scancode interact = SDL_SCANCODE_E;
};


class Player {
private:
    uint8_t player_speed;
    bool is_moving_left;

public:

    Bindings bindings;
    Animated_Sprite animated_sprite;
    std::map<SDL_Scancode,bool> actions;
    bool is_idle;
    SDL_Rect collision;
    

    Player(){
        bindings = Bindings();
        animated_sprite = Animated_Sprite();
        actions = std::map<SDL_Scancode,bool>();
        actions.insert({bindings.forwards,false});
        actions.insert({bindings.backwards,false});
        actions.insert({bindings.left,false});
        actions.insert({bindings.right,false});
        actions.insert({bindings.interact,false});
        is_idle = true;
        is_moving_left = false;
        player_speed = 4;
        collision = SDL_Rect();
        collision.h = 16*PLAYER_SIZE;
        collision.w = 16*PLAYER_SIZE;
    };

    // Maybe implement Boolean type (false on fail)
    void init_sprite(SDL_Renderer* renderer, std::string sprite_file, int w, int h, int x, int y)
    {
        animated_sprite = Animated_Sprite(renderer,sprite_file,w,h,x,y);
        // Stupid and shitty solution, will fix when I care
        animated_sprite.current_sprite.position_rect.w = PLAYER_SIZE * w;
        animated_sprite.current_sprite.position_rect.h = PLAYER_SIZE * h;
    }

    bool interact_toggle;

    void pause() {
        actions[bindings.forwards] = false;
        actions[bindings.backwards] = false;
        actions[bindings.left] = false;
        actions[bindings.right] = false;
    }

    void handle_keydown(SDL_Scancode key_sym)
    {
        if(actions.contains(key_sym)) {
            actions[key_sym] = true;
        }


        if(key_sym == bindings.interact)
        {
            interact_toggle = true;
        }
    }

    void handle_keyup(SDL_Scancode key_sym)
    {
        if(actions.contains(key_sym))
        {
            actions[key_sym] = false;
        }
        if(key_sym == bindings.interact)
        {
            interact_toggle = false;
        }
    }
    
    void update_sprite(SDL_Renderer* renderer, Clock clock)
    {

        // makes interaction a pulse not a constant. should be done different later this poopy
        if(interact_toggle)
        {
            actions[bindings.interact] = false;
        }

        is_idle = true;
        if(actions[bindings.forwards])
        {
            animated_sprite.current_sprite.position_rect.y -= player_speed;
            is_idle = false;
        }
        if(actions[bindings.backwards])
        {
            animated_sprite.current_sprite.position_rect.y += player_speed;
            is_idle = false;
        }
        if(actions[bindings.left])
        {
            animated_sprite.current_sprite.position_rect.x -= player_speed;
            is_idle = false;
            is_moving_left = true;
        }
        if(actions[bindings.right])
        {
            animated_sprite.current_sprite.position_rect.x += player_speed;  
            is_idle = false;
            is_moving_left = false;
        }
        if(actions[bindings.sprint])
        {
            player_speed = 6;
        }
        else
        {
            player_speed = 4;
        }
        
        if(is_idle)
        {
            animated_sprite.start_animation("idle",false);
            animated_sprite.current_frame = 0;
        }
        else
        {
            animated_sprite.start_animation("run",true);
        }
        animated_sprite.update(renderer,clock,is_moving_left);
        collision.x = animated_sprite.current_sprite.position_rect.x+24;
        collision.y = animated_sprite.current_sprite.position_rect.y+40;
        // SDL_RenderDrawRect(renderer, &collision);
    }



};

#endif
