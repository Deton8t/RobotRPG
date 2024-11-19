#ifndef SPRITE
#define SPRITE
#include <map>
#include "SDL_error.h"
#include "SDL_render.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "utils.cpp"
#include <string>


class Sprite
{  
public:
    SDL_Texture* sprite_sheet;
    SDL_Rect frame;
    SDL_Rect position_rect;
    std::string file;
    Sprite(){}
    void destroy() {
        SDL_DestroyTexture(sprite_sheet);
    }
    Sprite(SDL_Renderer* _renderer, std::string file_path, int width, int height,int x, int y)
    {
        auto img = IMG_Load(file_path.c_str());
        sprite_sheet = SDL_CreateTextureFromSurface(_renderer,img);
        SDL_FreeSurface(img);
        file = file_path;
        if(sprite_sheet == nullptr)
        {
            std::cout << SDL_GetError() << "\n"; 
        }
        frame.h = height;
        frame.w = width;
        frame.x = 0;
        frame.y = 0;
        position_rect.h = height;
        position_rect.w = width;
        position_rect.x = x;
        position_rect.y = y;
    }

    Sprite(SDL_Texture* _sprite_sheet, int lw, int frame_num ) {
        sprite_sheet = _sprite_sheet;
        frame = {frame_num*lw, 0, lw,lw};
        position_rect = {0,0,lw,lw};
    }
    
    void load_sprite(SDL_Renderer* renderer, bool is_mirrored)
    {
        if(is_mirrored)
        {
            SDL_RenderCopyEx(renderer, sprite_sheet, &frame, &position_rect, 0, NULL, SDL_FLIP_HORIZONTAL); 
            return;
        }
        if(SDL_RenderCopy(renderer,sprite_sheet,&frame,&position_rect) < 0)
        {
            std::cout << SDL_GetError() << "\n";
        }
    }
    void set_frame(int row, int col)
    {
       frame.x = col*frame.w;
       frame.y = row*frame.h;
    }
};
class Animated_Sprite
{
    public:
        Sprite current_sprite;
        std::map<std::string,Anim> animations; 
        int current_frame;
        bool is_looping;
        int idle_frame;
        std::string current_anim_name;
        int time_between_frames_ms;
        Animated_Sprite() : current_sprite(Sprite()){};
        Animated_Sprite(SDL_Renderer* renderer, std::string file_path, int width, int height, int x, int y) :current_sprite(Sprite(renderer,file_path,width,height,x,y))
        {
            idle_frame = 0;
            current_frame = 0;
            current_anim_name = "none";
            time_between_frames_ms = 0;
        }
        void add_animation(std::string name, int start_frame, int end_frame, int frame_rate)
        {
            Anim animation = {start_frame,end_frame,frame_rate};
            animations.insert({name,animation}); 
        }
        void start_animation(std::string name, bool is_loop)
        {
            current_anim_name = name;
            is_looping = is_loop;
        }



        void update(SDL_Renderer* renderer,Clock clock, bool is_facing_left)
        {
            time_between_frames_ms += clock.delta_ms;
            if(current_anim_name != "none")
            {
              Anim animation = animations[current_anim_name];  
              if(can_change_frame(animation.frame_rate))
              {    
                  if(current_frame >= animation.end)
                  {
                      if(is_looping)
                      {
                          current_frame = animation.start;
                      }
                      else
                      {
                          // TODO Change this to play idle animation, (animation will be looped);
                          current_frame = idle_frame;
                      }
                  }
                  else
                  {
                      current_frame++;
                  }
              }
            }
            current_sprite.set_frame(0,current_frame);
            // std::cout << current_frame << "\n";
            current_sprite.load_sprite(renderer,is_facing_left);
            return;
        }
        void cancel_animation()
        {
            current_frame = idle_frame;
            current_anim_name = "none";
        }
private:
        bool can_change_frame(int frame_rate)
        {
           int frame_rate_in_ms = 1000/frame_rate;
           if( time_between_frames_ms >= frame_rate_in_ms ) 
           {
               time_between_frames_ms = 0;
               return true;
           }
           return false;
        }

};

#endif

                  

