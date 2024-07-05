#ifndef GRAPHICS_LIBCPP
#define GRAPHICS_LIBCPP

#include "./globals.cpp"
#include "SDL.h"
#include "SDL_render.h"

namespace graphics_helpers {
    void render_ui_box(int x, int y, int w, int h) {
        SDL_Rect white = {x,y,w,h}; 
        SDL_Rect black = {x+5,y+5,w-10,h-10};
        SDL_SetRenderDrawColor(globals::renderer, 255,255,255,255);
        SDL_RenderFillRect(globals::renderer, &white);
        SDL_SetRenderDrawColor(globals::renderer, 0,0,0,255);
        SDL_RenderFillRect(globals::renderer, &black);
    }
    void texture_render(SDL_Texture* tex, SDL_Rect frame, SDL_Rect pos){
        SDL_RenderCopy(globals::renderer,tex,&frame,&pos);
    }
};

#endif
