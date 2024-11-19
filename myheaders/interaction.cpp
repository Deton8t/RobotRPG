#ifndef INTERACTION
#define INTERACTION


#include <SDL.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include "SDL_scancode.h"
#include "sprite.cpp"
#include "utils.cpp"
#include "api.cpp"
#include "globals.cpp"
#include "dialogue.cpp"

namespace interaction {
         
    enum actor_tag {
        DOOR,    
        DIALOGUE,
    };

    enum enemy_type 
    {
        test   
    };

    struct static_actor {
        std::vector<actor_tag> tags;
        SDL_Rect collision_box;
        Sprite sprite;
        std::map<std::string, std::string>* string_fields = nullptr;
        std::map<std::string, int>* num_fields = nullptr;
    };

    struct moving_actor{
        actor_tag type;
        SDL_Rect collision_box;
        Animated_Sprite anim_sprite;
        std::map<std::string, std::string>* string_fields = nullptr;
        std::map<std::string, int>* num_fields = nullptr;
    };

    void init_string_fields(static_actor* actor){
        if (actor->string_fields == nullptr)
        {
            actor->string_fields = new std::map<std::string,std::string>();
        }
    }

    void init_num_fields(static_actor* actor){
        if (actor->num_fields == nullptr)
        {
            actor->num_fields = new std::map<std::string, int>();
        }
    }

    /* \param actor: static_actor to make door
    *  \param _exit: stage_name that goes with the "exit" key of the num_fields
    */
    void make_door(static_actor *actor, stage_names exit) {
        init_num_fields(actor);
        actor->tags.push_back(actor_tag::DOOR);
        actor->num_fields->insert({"exit",(int)exit});

    }

    void make_dialogue(static_actor *actor, std::string talking_sprite_file, std::string dialogue_file)
    {
        init_string_fields(actor);
        init_num_fields(actor);
        actor->tags.push_back(actor_tag::DIALOGUE);
        actor->string_fields->insert({"talking_sprite", talking_sprite_file}); //talking_sprite
        actor->string_fields->insert({"dialogue", dialogue_file});
    }
    namespace {
        std::vector<std::string> parse_dialogue(std::string file_name)
        {
            std::ifstream ifs(file_name);
            std::vector<std::string> parsed = std::vector<std::string>();
            std::string temp;
            while(std::getline(ifs,temp))
            {
                //std::cout << "line: \n";
                //std::cout << temp << "\n";
                parsed.push_back(temp);
            }
            ifs.close();
            return parsed;

        }
    };
    void tag_logic(static_actor* actor)
    {
        for(actor_tag tag : actor->tags)
        {
            if(tag == actor_tag::DOOR && is_colliding(globals::player->collision, actor->collision_box))
            {
                if(globals::player->actions[globals::player->bindings.interact])
                {
                    stage_api::set((stage_names)actor->num_fields->at("exit"));
                }
            }
            if(tag == actor_tag::DIALOGUE)
            {
                if(is_colliding(globals::player->collision, actor->collision_box))
                {
                    if(globals::player->actions[globals::player->bindings.interact])
                    {
                        if(dialogue::index == -1)
                        {
                            Sprite* t_sprite = new Sprite(globals::renderer,
                                    actor->string_fields->at("talking_sprite"),
                                    DIALOGUE_SPRITE_LW,
                                    DIALOGUE_SPRITE_LW,
                                    DIALOGUE_SPRITE_X,
                                    DIALOGUE_SPRITE_Y);
                            t_sprite->frame.h = GLOBAL_TSPRITE_SIZE;
                            t_sprite->frame.w = GLOBAL_TSPRITE_SIZE;
                            std::vector<std::string> dialogue =  
                                parse_dialogue(actor->string_fields->at("dialogue"));
                            dialogue::start(dialogue,t_sprite);
                        }
                        else
                        {
                            dialogue::advance();
                        }
                    }
                    dialogue::render_box();
                }
                else {
                    dialogue::idle();
                }
            }
        }
    }


    static_actor create_static_actor(int x, int y, int w, int h, std::string file_name)
    {
        static_actor s_actor;
        s_actor.collision_box.x = x;
        s_actor.collision_box.y = y;
        s_actor.collision_box.w = w;
        s_actor.collision_box.h = h;
        s_actor.sprite = Sprite(globals::renderer,file_name, w,h,x,y);
        return s_actor;
    }


    void trigger_fight(enemy_type enemy)
    {
        switch(enemy)
        {
            case test:
                break;
            default:
                break;
        }
    }
}
#endif
