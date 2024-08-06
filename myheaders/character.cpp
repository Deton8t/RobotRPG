#ifndef CHARACTER
#define CHARACTER
#include "./items.cpp"
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

typedef items::item_type equip_type;

typedef enum {
    BOT,
} chr_class;
struct total_stat {
    int value;
    int percentage;
    int get() {
        return value * (float)percentage/100.0;
    }
};

struct RPG_exp {
    unsigned long current, total;
};

namespace character {
    struct character { 
        std::string name;
        chr_class chr_class;
        u_int8_t level;
        std::map<std::string, u_int8_t> base_stats;
        std::map<std::string, total_stat> total_stats;
        std::vector<items::item*> equips;
    };
    namespace {
        void stat_math(character* chr, items::i_stat *stat) {
            if(stat->is_percentage) {
                chr->total_stats.at(stat->name).percentage += stat->value;
                return;
            }
            chr->total_stats.at(stat->name).value += stat->value; 
        }
    }
    void calculate_stats(character* chr) {
            for(const auto& [key, value] : chr->base_stats) {
                total_stat t_stat;
                t_stat.value = value;
                t_stat.percentage = 100;
                chr->total_stats.insert_or_assign(key,t_stat);
            }
            for(const items::item* item : chr->equips) {
                if(item == nullptr)
                    break;
                for(items::i_stat stat : item->stats) {
                    stat_math(chr,&stat);
                }
            }
    }

}

#endif
