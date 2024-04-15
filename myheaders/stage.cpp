#ifndef STAGE
#define STAGE

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "./utils.cpp"
#include "./sprite.cpp"
#include "SDL_render.h"

#define TILE_WIDTH  32;
#define TILE_HEIGHT  32;


#define STAGE_TILESETS_FOLDER "./stages/tilesets"
#define STAGE_MUSIC_FOLDER "./stages/music"



namespace Stage
{
    enum objects 
    {
        INTERACTABLE,
        ENTITY,
    };
	

	class Level_Object
    {
        public:
            // Because tiles pos is considered the top left of 32x32 tile
            SDL_Rect position_rect;
            
            Sprite sprite;

             Level_Object(int x, int y)
            {
                position_rect.x = x;
                position_rect.y = y;
                position_rect.h = TILE_HEIGHT;
                position_rect.w = TILE_WIDTH;
            }

            // render tile, render sprite
            void update(SDL_Renderer *renderer)
            { 
                sprite.load_sprite(renderer,false);
            }
    };

	class Enemy
	{
	    
	};


	class Interactable : Level_Object
    {	
        public:
            SDL_Rect trigger;
    };

    class Tile
    {
        public:
            SDL_Rect tile_rect;
            SDL_Rect pos_rect;
            Level_Object object;
            // @param pos_x posisition in level on x
            // @param pos_y position in level on y
            // @param tile_x position of x for tile texture
            // @param tile_y position of y for tile texture
            Tile(int pos_x, int pos_y, int tile_x, int tile_y) : object(Level_Object(pos_x,pos_y))
            {
                object = Level_Object(pos_x,pos_y); 
                tile_rect.x =  tile_x * TILE_WIDTH;
                tile_rect.y =  tile_x * TILE_HEIGHT;
                tile_rect.h = TILE_HEIGHT;
                tile_rect.w = TILE_WIDTH;
                
                pos_rect.x = pos_x;
                pos_rect.y = pos_y;
                pos_rect.h = TILE_HEIGHT;
                pos_rect.w = TILE_WIDTH;
            }
            void update(SDL_Renderer* renderer, SDL_Texture* tileset)
            {
                SDL_RenderCopy(renderer, tileset, &tile_rect, &pos_rect);
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


    // currently does not support background objects
    Stage load_stage(SDL_Renderer* renderer, std::string background_file, std::string name, std::string bg_music_name)
    {
        Stage stage;
        // This is pretty long and convoluted but should work;
        SDL_Texture* tileset_texture = SDL_CreateTextureFromSurface(renderer,IMG_Load((STAGE_MUSIC_FOLDER + background_file).c_str()));
        stage.level_tiles = std::vector<Tile>();
        stage.tileset = tileset_texture;
        stage.name = name;
        stage.bg_music_name = bg_music_name;
        return stage;
    }
        

};

#endif
