#ifndef MENUS_CPP
#define MENUS_CPP
#include <SDL.h>
#include <SDL_ttf.h>
#include "font.cpp"
#include "globals.cpp"

namespace menus {
    void display_text(SDL_Rect text_box, std::string text, u_int8_t pt)
    {
        text_box.w = text.size() * pt;
        text_box.h = pt*2;
        font::render(font::cave_story, &text_box, text);
    }
    // 16pt by default
    void display_text(SDL_Rect text_box, std::string text)
    {
        display_text(text_box,text,16);
    }

    SDL_Rect render_ui_box(int x, int y, int w, int h) {
        SDL_Rect white = {x,y,w,h}; 
        SDL_Rect black = {x+5,y+5,w-10,h-10};
        SDL_SetRenderDrawColor(globals::renderer, 255,255,255,255);
        SDL_RenderFillRect(globals::renderer, &white);
        SDL_SetRenderDrawColor(globals::renderer, 0,0,0,255);
        SDL_RenderFillRect(globals::renderer, &black);
        return {x,y,w,h};
    }

    SDL_Rect render_ui_box(SDL_Rect r) {
        return render_ui_box(r.x,r.y,r.w,r.h);
    }
}

#endif
