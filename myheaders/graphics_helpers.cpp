#ifndef GRAPHICS_LIBCPP
#define GRAPHICS_LIBCPP

#include "./globals.cpp"
#include "SDL.h"
#include "SDL_render.h"

namespace graphics_helpers {
    void texture_render(SDL_Texture* tex, SDL_Rect frame, SDL_Rect pos){
        SDL_RenderCopy(globals::renderer,tex,&frame,&pos);
    }
};

#endif
