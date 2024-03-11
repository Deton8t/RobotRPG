#include <map>

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
    explicit Sprite(SDL_Renderer* _renderer, std::string file_path, int width, int height,int x, int y)
    {
        sprite_sheet = SDL_CreateTextureFromSurface(_renderer,IMG_Load(file_path.c_str()));

        frame.h = height;
        frame.w = width;
        frame.x = 0;
        frame.y = 0;
        position_rect.h = height*4;
        position_rect.w = width*4;
        position_rect.x = x;
        position_rect.y = y;

    }

    void load_sprite(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer, sprite_sheet, &frame, &position_rect); 
    }
    void set_sprite(int row, int col)
    {
       frame.x = col*frame.w;
       frame.y = row*frame.h;
    }
};
class Animated_Sprite
{
    public:
        Sprite sprite;
        std::map<std::string,anim> animations; 
        int current_frame;
        bool is_looping;
        int idle_frame;
        std::string current_anim_name;
        int time_between_frames_ms;

        explicit Animated_Sprite(SDL_Renderer* renderer, std::string file_path, int width, int height, int x, int y) : sprite(Sprite(renderer,file_path,width,height,x,y))
        {
            idle_frame = 0;
            current_frame = 0;
            current_anim_name = "none";
            time_between_frames_ms = 0;
        }
        void add_animation(std::string name, int start_frame, int end_frame, int frame_rate)
        {
            anim animation = {start_frame,end_frame,frame_rate};
            animations.insert({name,animation}); 
        }
        void start_animation(std::string name, bool is_loop)
        {
            current_anim_name = name;
            is_looping = is_loop;
        }



        void update(SDL_Renderer* renderer,Clock clock)
        {
            time_between_frames_ms += clock.delta_ms;
            if(current_anim_name != "none")
            {
              anim animation = animations[current_anim_name];  
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
            sprite.set_sprite(0,current_frame);
            // std::cout << current_frame << "\n";
            sprite.load_sprite(renderer);
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
           if(frame_rate_in_ms < time_between_frames_ms)
           {
               time_between_frames_ms = 0;
               return true;
           }
           return false;
        }

};

/* Creates a sprite when given a filepath to spritesheet
*/
// Sets the sprite to be loaded based on which sprite it is in spritesheet (start at 0)
