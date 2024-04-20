#ifndef STAGE
#define STAGE

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "./utils.cpp"
#include "./sprite.cpp"
#include "SDL_render.h"

#define TILE_WIDTH  32
#define TILE_HEIGHT  32
#define STAGE_WIDTH 32
#define STAGE_HEIGHT 20


#define STAGE_TILESETS_FOLDER "./images/tilesets"
#define STAGE_MUSIC_FOLDER "./music"



namespace Stage
{
    enum object_names 
    {
        NONE,
        INTERACTABLE,
        ENTITY,
    };


    struct Level_Object
    {
        std::string name;
        SDL_Texture* texture_rect;
    };

   class Tile
    {
        public:
            SDL_Rect tile_rect;
            SDL_Rect pos_rect;
            // Objects will be handled separately
            Level_Object* object;
            // @param pos_x posisition in level on x
            // @param pos_y position in level on y
            // @param tile_x position of x for tile texture
            // @param tile_y position of y for tile texture
            Tile(int pos_x, int pos_y, int tile_x, int tile_y)
            {
                tile_rect.x =  tile_x * TILE_WIDTH;
                tile_rect.y =  tile_x * TILE_HEIGHT;
                tile_rect.h = TILE_HEIGHT;
                tile_rect.w = TILE_WIDTH;

                pos_rect.x = pos_x;
                pos_rect.y = pos_y;
                pos_rect.h = TILE_HEIGHT;
                pos_rect.w = TILE_WIDTH;

                object = nullptr;

            }

            void update(SDL_Renderer* renderer, SDL_Texture* tileset)
            {
                SDL_RenderCopy(renderer, tileset, &tile_rect, &pos_rect);
            }
            
            void add_object(object_names name)
            {
                switch(name)
                {
                    case NONE:
                        object = nullptr;
                    case INTERACTABLE:
                        object = new Level_Object;
                        object->name = "INTERACTABLE";
                        object->texture_rect = nullptr;
                    default:
                        object = nullptr;
                        std::cout << "You fucked up the name lil bro";
                }
            }
    };

    struct Stage
    {
        std::vector<Tile> level_tiles;         
        Point2D spawn_point;
        SDL_Texture* tileset;  
        std::string name;
        std::string bg_music_name;
    };


    Stage init_stage(SDL_Renderer* renderer, std::string tile_sheet, std::vector<int> tile_nums, std::string name, std::string bg_music_name) {
        Stage stage;
        // This is pretty long and convoluted but should work;
        SDL_Texture* tileset_texture = SDL_CreateTextureFromSurface(renderer,IMG_Load((STAGE_MUSIC_FOLDER + tile_sheet).c_str()));
        stage.level_tiles = std::vector<Tile>();
        for(int i = 0; i < tile_nums.size(); i++)
        {
            stage.level_tiles.push_back(Tile(i*TILE_WIDTH, (i/STAGE_WIDTH)*STAGE_HEIGHT, tile_nums[i], 0));
        }
        stage.tileset = tileset_texture;
        stage.name = name;
        stage.bg_music_name = bg_music_name;
        return stage;
    }

    void render_stage(SDL_Renderer* renderer, Stage stage)
    {
        SDL_RenderClear(renderer);
        for(Tile tile : stage.level_tiles)
            tile.update(renderer,  stage.tileset);
    }



};

#endif
