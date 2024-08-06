#ifndef PARTYCPP
#define PARTYCPP
#include "items.cpp"
#include "character.cpp"
namespace party {
    std::vector<character::character> party = std::vector<character::character>();
    std::vector<items::item> player_items = std::vector<items::item>();

    void equip(character::character* chr, items::item* _item) {
        if(chr == nullptr || _item == nullptr)
            std::cout << "EQUIP FAILURE!!!! (nullptr)\n";
        chr->equips[_item->type] = _item;
    }
    void start(){
        party.push_back({
                "Robot", //name
                chr_class::BOT, //class
                1, //level
                {
                    {"HYD",1},
                    {"BST",1},
                    {"ITG",1},
                    {"CHR",1},
                    {"SYC",1},
                    {"BOD",1}
                }, //base_stats
                {}, //total stats
                {nullptr,nullptr,nullptr,nullptr,nullptr}, //equips
                });
        character::calculate_stats(&party[0]);
    }

    void add(character::character chr) { party.push_back(chr); }


    character::character* get(int index) { return &party[index]; } 


}

#endif

