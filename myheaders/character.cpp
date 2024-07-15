#ifndef CHARACTER
#define CHARACTER
#include "./items.cpp"
#include <cstdint>
#include <iostream>
#include <vector>

typedef items::item_type equip_type;

typedef enum {
    ROBBIT,
} chr_class;

struct RPG_exp {
    unsigned long current, total;
};

namespace character {
    struct character { 
        std::string name;
        chr_class chr_class;
        u_int8_t level;
        std::map<std::string, u_int8_t> base_stats;
        std::map<std::string, u_int8_t> total_stats;
        std::vector<items::item*> equips;
    };
    namespace {
        void stat_math(character* chr, items::i_stat *stat) {
            if(stat->is_percentage) {
                chr->total_stats.at(stat->name) *= (1.0 + stat->value/100.0);
                return;
            }
            chr->total_stats.at(stat->name) += stat->value; 
        }
    }
    void calculate_stats(character* chr) {
            for(const auto& [key, value] : chr->base_stats) {
                chr->total_stats.at(key) = value;
            }
            for(const items::item* item : chr->equips) {
                if(item == nullptr)
                    break;
                for(items::i_stat stat : item->stats) {
                    stat_math(chr,&stat);
                }
            }
    }

    character make_character(std::string name, chr_class _class) {
        character chr {name,_class,1};
        for(uint8_t i; i < sizeof(equip_type); i++) {
                chr.equips.push_back(nullptr);
        }
        return chr;

    }

    void equip(character* chr, items::item* _item) {
        if(chr == nullptr || _item == nullptr)
            std::cout << "EQUIP FAILURE!!!! (nullptr)\n";
        chr->equips[_item->type] = _item;
    }
}

#endif
