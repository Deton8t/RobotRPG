#ifndef STAGE
#define STAGE

#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <SDL_render.h>
#include "interaction.cpp"
#include "music.cpp"
#include "globals.cpp"
#include "api.cpp"

#define TILE_WIDTH  64
#define TILE_HEIGHT  64
#define STAGE_WIDTH 16
#define STAGE_HEIGHT 10


#define STAGE_TILESETS_FOLDER "./images/tilesets/"



namespace stage
{
    stage_names id; 
    std::string name;
    std::string music_name;
    std::vector<interaction::static_actor> s_actors;
    std::vector<interaction::moving_actor> m_actors;
    namespace{
        SDL_Texture* tileset;
        SDL_Renderer* renderer;
        std::vector<int> tile_nums;
        int int_from_string(std::string s) {
            int parsed_int = 0;
            bool is_neg = false;
            if(s[0] == '-')
            {
                is_neg = true;
            }
            for(int i = 0 + is_neg; i < s.length(); i++)
            {
                if(is_neg)
                {
                    parsed_int -= (s[i] - '0') * pow(10,s.length()-1-i);
                }
                else {
                    parsed_int += (s[i] - '0') * pow(10,s.length()-i - 1);
                }
            }
            return parsed_int;
        }
        void tiles_from_csv(std::string filename)
        {
            tile_nums.clear();
            std::fstream tile_file;
            std::string complete_filename = "./stages/";
            complete_filename.append(filename);
            tile_file.open(complete_filename, std::iostream::in);
            std::string line;
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 15; j++)
                {
                    std::getline(tile_file,line,',');
                    tile_nums.push_back(int_from_string(line));
                    //std::cout << int_from_string(line) << " ";

                }
                std::getline(tile_file,line,'\n');
                //std::cout << int_from_string(line) << "\n";
                tile_nums.push_back(int_from_string(line));
            }
        }
    }

    // Renders the stage
    void stage_draw()
    {
        // Screen is 16x10 tiles which are 64x64 pixels tiles are called chunks here
        // As the tile prefix will be used to refer to the position on tilesheet
        // tilesheet rows are 10 tiles in width
        for(int chunk_row = 0; chunk_row < STAGE_HEIGHT; chunk_row++)
        {
            for(int chunk_col = 0; chunk_col < STAGE_WIDTH; chunk_col++)
            {
                SDL_Rect tile_rect;
                tile_rect.x = (tile_nums[chunk_row*STAGE_WIDTH + chunk_col] % 10) * TILE_WIDTH;
                tile_rect.y =  (tile_nums[chunk_row*STAGE_WIDTH + chunk_col] / 10) * TILE_HEIGHT;
                tile_rect.w = TILE_WIDTH;
                tile_rect.h = TILE_HEIGHT;
                SDL_Rect tile_pos_rect;
                tile_pos_rect.x = chunk_col * TILE_WIDTH;
                tile_pos_rect.y = chunk_row * TILE_HEIGHT;
                tile_pos_rect.w = TILE_WIDTH;
                tile_pos_rect.h = TILE_HEIGHT; 
                if(SDL_RenderCopy(renderer, tileset, &tile_rect, &tile_pos_rect) != 0)
                {
                    std::cout << SDL_GetError();
                    std::cout << "\n";
                }

            }
        }

    }

    void interactable_draw() {
        for(interaction::static_actor s_actor : s_actors)
        {
            s_actor.sprite.load_sprite(stage::renderer, false);
        }
        for(interaction::moving_actor m_actor : m_actors)
        {
            m_actor.anim_sprite.update(globals::renderer, *globals::clock, false);
        }
    }

    void set(stage_names stage_name)
    {
        s_actors.clear();
        m_actors.clear();
        switch(stage_name)
        {
            case TEST:
                name = "Test";
                music_name = "ForJaden.mp3";
                s_actors.push_back(interaction::create_static_actor(4*32,5*32,32,32,"images/sprites/chest.png"));
                interaction::make_door(&s_actors[0],stage_names::RANDOM);
                s_actors.push_back(interaction::create_static_actor(8*32,5*32,32,32,"images/sprites/chest.png"));
                interaction::make_dialogue(&s_actors[1], "images/sprites/chest.png", "./stages/Test/dialogue/chest.txt");
                tileset = SDL_CreateTextureFromSurface(renderer, IMG_Load("./images/tilesheets/TestTiles.png"));
                tiles_from_csv("Test/Test.csv");
                music::play_music(music_name, true);
                break;

            case RANDOM:
            default:
                name = "Random";
                music_name = "ForJaden.mp3";
                tileset = SDL_CreateTextureFromSurface(renderer, IMG_Load("./images/tilesheets/TestTiles.png"));
                if(tileset == NULL)
                {
                    std::cout << SDL_GetError();
                    std::cout << "\n";
                }
                tile_nums.clear();
                for(int i = 0; i < 20*32; i++)
                {
                    tile_nums.push_back(random()%4);
                }
                music::play_music(music_name, true);
                s_actors.push_back(interaction::create_static_actor(10*32,7*32,32,32,"images/sprites/chest.png"));
                interaction::make_door(&s_actors[0],stage_names::TEST);
                break;
        }
    }

    void handle_actors()
    {  
      for(interaction::static_actor actor : s_actors)
      {
          interaction::tag_logic(&actor);
      }
    }

    void update()
    {
        stage_draw();
        interactable_draw();
        handle_actors();
    }

    // Initialize anything that needs to happen for any stage to exist
    void init(SDL_Renderer* stage_renderer)
    {
        renderer = stage_renderer;
        stage_api::set = &set;

    }

};


#undef TILE_WIDTH  
#undef TILE_HEIGHT 
#undef STAGE_WIDTH 
#undef STAGE_HEIGHT
#undef STAGE_TILESETS_FOLDER 

#endif
