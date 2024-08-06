#ifndef SAVECPP
#define SAVECPP
#include "globals.cpp"
#include "items.cpp"
#include "character.cpp"
#include "inventory.cpp"
#include "tomlcpp.hpp"
#include "stage.cpp"

#include "./party.cpp"
#include <format>
#include <iostream>
#include <string>
#include "string_view"
#include <vector>
#include <fstream>

using namespace items;
namespace save {
    namespace helpers{
    };
    void items() {
        std::ofstream inv = std::ofstream("saves/inventory.toml");
        inv.flush();
        if(inventory::player_items.size() == 0) {
            return;
        }
        for(int i = 0; i < inventory::player_items.size(); i++)
        {
            item current_item = inventory::player_items[i];
            inv << "[[items]]\n";
            inv << "name = \"" << current_item.name << "\"\n";
            inv << "type = " << (int)current_item.type << "\n";
            inv << "sprite-id = "    << (int)current_item.sprite_id << "\n";
            for(i_stat stat : current_item.stats) {
                inv << "[[items.stats]]\n";
                inv << "name = \"" << stat.name << "\"\n";
                inv << "value = " << std::to_string(stat.value) << "\n";
                inv << "percentage = " << std::to_string(stat.is_percentage) << "\n";
            }
            inv << "\n";

        }
        inv.close();
    }
    void party() {
        std::ofstream p_file = std::ofstream("saves/party.toml");
        if(!p_file) {
            std::cout << " PARTY FILE SAVE FAILURE!!!\n";
            return;
        }
        for(character::character member : party::party) {
            p_file << "[[member]]\n";
            p_file << "name = " << member.name << "\n";
            p_file << "class = " << member.chr_class << "\n";
            p_file << "level = " << (int)member.level << "\n";
            p_file << "equip_index = [";
            for(int i = 0; i < member.equips.size()-1; i++) {
                if(member.equips[i] != nullptr) {
                    p_file << (int)member.equips.at(i)->index<< ",";
                }
                else { 
                    p_file << "-1" << ",";
                }
            }
            p_file << (int)member.equips[member.equips.size()-1]->index<< "]\n";

            for(const auto& [key,value] : member.base_stats)
            {
                p_file << key << " = " << (int)value << "\n";
            }
            p_file << "\n";
        }
        p_file.close();
    }
    void stage() {
        std::ofstream s_file = std::ofstream("saves/stage.toml");
        if(!s_file) {
            std::cout << " STAGE FILE SAVE FAILURE!!!\n";
            return;
        }
        s_file << "[stage]\n"; 
        s_file << "id = " << (int)stage::id << "\n";
        s_file << "player.x = " << globals::player->get_pos_rect()->x << "\n";
        s_file << "player.y  = " << globals::player->get_pos_rect()->y;
    }
};
namespace load {
    namespace {
        void error(std::string msg) {
            std::cerr << "ERROR: " << msg << "\n";
            exit(1);
        }
    };
    void items() {
       toml::Result res = toml::parseFile("saves/inventory.toml"); 
       if(!res.table) {
           error(res.errmsg);
       }
       auto items = res.table->getArray("items");
       if(!items) {
            error("missing [[items]]");
       }
       for(int i = 0; i < items->size(); i++) {
            items::item _item;
            auto current_table = items->getTable(i);
            if(!current_table) {
                error(std::format("Missing [[items]] entry #%d", i));
            }
            auto [ok,name] = current_table->getString("name");
            if(!ok) {
                error(std::format("Name entry wrong on !! on table #%d,",i));
            }
            _item.name = name;
            auto type = current_table->getInt("type");
            if(!type.first) {
                error(std::format("type entry wrong on table #%d", i));
            }
            _item.type = (item_type)type.second;
            auto id = current_table->getInt("sprite-id");
            if(!type.first) {
                error(std::format("id entry wrong on table #%d",i));
            }
            _item.sprite_id = id.second;

            auto stats = current_table->getArray("stats");
            if(!stats)
            {
                error("item.stats array is buggin, king");
            }
            for(int stat_index = 0; stat_index < stats->size(); stat_index++) {
                auto current_table = stats->getTable(stat_index);
                items::i_stat stat;
                stat.name = current_table->getString("name").second;
                stat.value = current_table->getInt("value").second;
                stat.is_percentage = (bool)current_table->getInt("percentage").second;
                _item.stats.push_back(stat);
            }
            inventory::give(_item);
       }
       
    }
    void party();
    void stage();
};

#endif
