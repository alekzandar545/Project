#pragma once
#include <string>

class Item{
public:
    enum class ItemType{
        Weapon,
        Spell,
        Armor
    };
    //getters
    ItemType GetType() const{
        return this->type;
    }
    unsigned GetPower() const{
        return this->power;
    }
    std::string GetName() const{
        return this->name;
    }
private:
    ItemType type;
    std::string name;
    unsigned power;
};