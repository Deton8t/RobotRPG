#ifndef MUSIC
#define MUSIC

#include "SDL_audio.h"
#include "SDL_filesystem.h"
#include <iostream>
#include <string>
#include <SDL_mixer.h>
#define Music_Sound Mix_Chunk 

namespace music {

    void init_music()
    {
        Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK);
        Mix_OpenAudio(48000,AUDIO_F32SYS , 2, 2048);
    }
    // Loads song from file into memory and plays it
    void play_music(std::string file_name, bool is_looping)
    {
        std::string path = SDL_GetBasePath();
        path.append("/music/" + file_name);
        Mix_Music* song = Mix_LoadMUS(path.c_str()); 
        if( song == nullptr)
        {
            std::cout << "Couldn't load song :(: " << Mix_GetError() << "\n";
        }
        Mix_PlayMusic(song, -1*is_looping );
    }

    // Stores audio clip into memory
    Music_Sound* load_sound(std::string file_name)
    {
        return Mix_LoadWAV(file_name.c_str());
    }

    // Plays a sound on a free channel with 0 loops
    void play_sound(Music_Sound* sound)
    {
        Mix_PlayChannel(-1, sound, 0);
    }

}

#endif
