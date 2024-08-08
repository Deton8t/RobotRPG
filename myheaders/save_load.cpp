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
            p_file << "name = \"" << member.name << "\"\n";
            p_file << "class = " << member.chr_class << "\n";
            p_file << "level = " << (int)member.level << "\n";
            p_file << "equip_index = [";
            for(int i = 0; i < member.equips.size()-1 ; i++) {
                if(member.equips[i] != nullptr) {
                    p_file << (int)member.equips.at(i)->index<< ",";
                }
                else { 
                    p_file << "-1" << ",";
                }
            }
            if(member.equips[member.equips.size()-1] != nullptr) {
                p_file << (int)member.equips[member.equips.size()-1]->index<< "]\n";
            }
            else { 
                p_file << "-1" << "]\n";
            }
            p_file << "stats = [";
            for(const auto& [key,value] : member.base_stats) {
                p_file << "\"" << key << "\"," << (int)value << ",\n";
            }
            p_file << "]\n";
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
            std::cerr << "toml PARSE ERROR: " << msg << "\n";
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
                error(std::format("ITEMS -> Missing [[items]] entry #{}", i));
            }
            auto [ok,name] = current_table->getString("name");
            if(!ok) {
                error(std::format("ITEMS -> Name entry wrong on !! on table #{},",i));
            }
            _item.name = name;
            auto type = current_table->getInt("type");
            if(!type.first) {
                error(std::format("ITEMS -> type entry wrong on table #{}", i));
            }
            _item.type = (item_type)type.second;
            auto id = current_table->getInt("sprite-id");
            if(!type.first) {
                error(std::format("ITEMS -> id entry wrong on table #{}",i));
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
    void party() {
        auto file = toml::parseFile("saves/party.toml"); 
        if(!file.table) {
            error("party.toml " + file.errmsg);
        }
        auto toml_party = file.table->getArray("member");
        if(!toml_party) {
            std::cout << "Empty PARTY save file\n";
            party::start();
            return;
        }
        for(int i = 0; i < toml_party->size(); i++) {
            auto current_member = toml_party->getTable(i);
            character::character chr;
            if(!current_member) {
                error(std::format("party.toml-> member {} missing ", i));
            }

            auto try_name = current_member->getString("name");
            if(!try_name.first) {
                
                error(std::format("party.toml-> member {} missing name", i));
            }
            chr.name = try_name.second;

            auto try_class = current_member->getInt("class");
            if(!try_class.first) {
                
                error(std::format("party.toml-> member {} missing class", i));
            }
            chr.chr_class = (chr_class)try_class.second;

            auto try_level= current_member->getInt("level");
            if(!try_level.first) {
                
                error(std::format("party.toml-> member {} missing level", i));
            }
            chr.level = (chr_class)try_level.second;

            auto equips = current_member->getArray("equip_index");
            if(!equips) {
                
                error(std::format("party.toml-> member {} missing equips", i));
            }
            for(int e_idx = 0; e_idx < equips->size(); e_idx++) {
                auto try_equip = equips->getInt(e_idx);
                if(!try_equip.first) {
                    error(std::format("party.toml-> member {} missing equip at index {}", i,e_idx));
                }
                if((int)try_equip.second != -1) {
                    chr.equips.push_back(&inventory::player_items[try_equip.second]); 
                }
                else {
                    chr.equips.push_back(nullptr);
                }
            }
            auto stats = current_member->getArray("stats");
            if(!stats) {
                
                error(std::format("party.toml-> member {} missing stats", i));
            }
            for(int s_idx = 0; s_idx < stats->size()-1; s_idx+= 2) {
                auto try_str = stats->getString(s_idx); 
                auto try_int = stats->getInt(s_idx+1);
                if(!try_str.first || !try_int.first) {
                    error(std::format("party.toml-> member {} missing stat at {}", i,s_idx));
                }
                chr.base_stats.insert_or_assign(try_str.second,(u_int8_t)try_int.second);
                std::cout << "index: " << s_idx << " key: " << try_str.second << " int: " << try_int.second << "\n";
            }
            party::add(chr);
        }
    };

    void stage() {
        auto stage_file = toml::parseFile("saves/stage.toml");
        if(!stage_file.table) {
            error(stage_file.errmsg);        
        }
        auto stage_table = stage_file.table->getTable("stage");
        if(!stage_table) {
            return;
        }
        auto try_id = stage_table->getInt("id"); 
        if(!try_id.first) {
            error("Cant find [stage.id] ");
        }
        stage::set((stage_names)try_id.second);
        auto player_table = stage_table->getTable("player");
        if(!player_table) {
           error("Player table parsing error!"); 
        }
        auto try_x = player_table->getInt("x");
        if(!try_x.first) {
            error("player x wrong!");
        }
        globals::player->get_pos_rect()->x = try_x.second;
        auto try_y = player_table->getInt("y");
        if(!try_y.first) {
            error("player y wrong!");
        }
        globals::player->get_pos_rect()->y = try_y.second;
    }
};

#endif
