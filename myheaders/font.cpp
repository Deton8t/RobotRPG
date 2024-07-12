#ifndef FONT
#define FONT

#include "SDL_error.h"
#include "SDL_pixels.h"
#include <SDL_ttf.h>
#include <iostream>
#include "./globals.cpp"
#include "SDL_render.h"
namespace font {
    
    TTF_Font* cave_story;
    /* Inits SDL2_ttf and sets up "cave_story" font
     */
    void init()
    {
        if(TTF_Init() == -1)
            std::cout << "TTF ERROR: " << SDL_GetError() << "\n";
        cave_story = TTF_OpenFont("./fonts/Cave-Story.ttf",30);
        if(cave_story == NULL)
        {
            std::cout << SDL_GetError() << "\n";
        }
    }

    void render(TTF_Font* font, SDL_Rect* dst, std::string message) {
        //dst->w = message.size()*20;
        SDL_Texture* text = SDL_CreateTextureFromSurface(globals::renderer, TTF_RenderUTF8_Solid(font,message.c_str(), {255,255,255,255}));
        if(text == NULL)
        {
            std::cout << SDL_GetError() << "\n";

        }
        SDL_RenderCopy(globals::renderer, text, NULL, dst);
    }

}

#endif
