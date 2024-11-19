#ifndef MUSIC
#define MUSIC

#include "SDL_audio.h"
#include "SDL_filesystem.h"
#include <iostream>
#include <string>
#include <SDL_mixer.h>
#include <thread>
#include <vector>
#define Music_Sound Mix_Chunk 

#define CHANNEL_GROUP_MUSIC 0
#define CHANNEL_GROUP_CHUNK 1

namespace music {
    Mix_Music* song = nullptr;
    std::vector<Mix_Chunk*> chunks; 
    void init_music()
    {
        Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK);
        Mix_OpenAudio(48000,AUDIO_F32SYS , 2, 2048);
        Mix_GroupChannels(1, 20, CHANNEL_GROUP_CHUNK);
    }
    // Loads song from file into memory and plays it
    void play_music(std::string file_name, bool is_looping)
    {
        std::string path = SDL_GetBasePath();
        path.append("/music/" + file_name);
        song = Mix_LoadMUS(path.c_str()); 
        if( song == nullptr)
        {
            std::cout << "Couldn't load song :(: " << Mix_GetError() << "\n";
        }
        Mix_PlayMusic(song, -1*is_looping );
    }
    void close_music() {
        Mix_HaltMusic();
        if(song != nullptr) {
            Mix_FreeMusic(song);
        }
    }

    // Stores audio clip into memory
    Music_Sound* load_sound(std::string file_name)
    {
        return Mix_LoadWAV(file_name.c_str());
    }
    void cull_chunk(Mix_Chunk* chunk, int time_s) {
        std::this_thread::sleep_for(std::chrono::seconds(time_s));
        Mix_FreeChunk(chunk);
    }

    // Plays a sound on a free channel with 0 loops
    void play_sound(Music_Sound* sound, int length_s)
    {
        Mix_PlayChannel(-1, sound, 0);
        std::thread(cull_chunk,sound,length_s).detach();
    }

    void play_sound_from_file(std::string file_name, int length_s)
    {
        auto chunk = load_sound(file_name.c_str());
        play_sound(chunk,length_s);
        chunks.push_back(chunk);
    }
    void clean() {
        for(auto chunk : chunks) {            
            if(chunk) {
                Mix_FreeChunk(chunk);
            }
        }
        chunks.clear();
        chunks.shrink_to_fit();
    }


}

#endif
