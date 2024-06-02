#pragma once
#include <string>

class Item {
public:
    enum class ItemType {
        Weapon,
        Spell,
        Armor,
        Potion
    };
    // Constructors
    Item();
    Item(const std::string& name, ItemType type, unsigned power);
    Item(const Item& other);          
    Item& operator=(const Item& other);
    ~Item();              
    // Static method to generate an item
    static Item GenerateItem(unsigned level);
    // Getters
    ItemType GetType() const;
    unsigned GetPower() const;
    std::string GetName() const;      
private:
    ItemType type;
    std::string name;
    unsigned power;
};