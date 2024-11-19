#ifndef DIALOGUECPP
#define DIALOGUECPP
#include "./globals.cpp"
#include "./sprite.cpp"
#include "./font.cpp"
#include "SDL_mixer.h"
#include "SDL_render.h"
#include "music.cpp"
#include <SDL.h>
#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#define DIALOGUE_SPRITE_X 10
#define DIALOGUE_SPRITE_Y 441
#define DIALOGUE_SPRITE_LW 180

namespace {
#define LINE_WIDTH 764
#define CHAR_WIDTH 20
#define CHARS_PER_LINE  LINE_WIDTH/(CHAR_WIDTH)
#define CHAR_HEIGHT 28
}

namespace dialogue {
    int index = -1; 
    std::vector<std::string> dialogue = std::vector<std::string>();
    Sprite* talking_sprite = nullptr;
    bool is_on() {
        return index != -1;
    }
    void start(std::vector<std::string> _dialogue, Sprite* _talking_sprite) {
        index = 0;
        dialogue = _dialogue;
        talking_sprite = _talking_sprite;
        music::play_sound_from_file("./sounds/dialogue_beep.mp3",3);
    }

    void stop() {
        index = -1;
        dialogue.clear();
        talking_sprite = nullptr;
    }
    void idle() {
        index = -1;
    }
    void render_box() {
        if(index == -1)
        {
            return;
        }
        SDL_Rect outline = {0+5,426+5,1024-10,213-10}; 
        if(SDL_SetRenderDrawColor(globals::renderer,255,255,255,255) < 0)
        {
            std::cout << SDL_GetError() << "hi!\n";
        }
        SDL_RenderFillRect(globals::renderer, &outline); 
        SDL_SetRenderDrawColor(globals::renderer,0,0,0,255);
        SDL_Rect inner_body = {5+5,431+5,1014-10,203-10};
        SDL_RenderFillRect(globals::renderer, &inner_body); 
        SDL_SetRenderDrawColor(globals::renderer,255,255,255,255);
        talking_sprite->load_sprite(globals::renderer, false);
        SDL_Rect font_rect = inner_body;
        font_rect.h = CHAR_HEIGHT;
        font_rect.x += 220;
        font_rect.y += 5;
        for(int i = 0; i < dialogue[index].size(); i += (CHARS_PER_LINE))
        {
            int offset = 0;
            while(i+CHARS_PER_LINE < dialogue[index].size() && dialogue[index][i+CHARS_PER_LINE-offset] != ' ')
                offset++;
            font_rect.w = dialogue[index].substr(i,CHARS_PER_LINE-offset).size() * 18;
            font::render(font::cave_story, &font_rect, dialogue[index].substr(i,CHARS_PER_LINE-offset));
            i = i - offset + 1;
            font_rect.y += 30;
        }
    }


    void advance() {
        index++;
        music::play_sound_from_file("./sounds/dialogue_beep.mp3", 3);
        if(index >= dialogue.size()) {
            stop();
        }
    }

    void clear() {
        index=0;
        dialogue.clear();
        talking_sprite = nullptr;
    }
    
};

#endif
