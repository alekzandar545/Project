#pragma once
#include <string>

class Item {
public:
    enum class ItemType {
        Weapon,
        Spell,
        Armor
    };

    // Getters
    ItemType GetType() const;
    unsigned GetPower() const;
    std::string GetName() const;

    // Constructors
    Item();
    Item(const std::string& name, ItemType type, unsigned power);
    Item(const Item& other);           // Copy constructor
    Item& operator=(const Item& other); // Copy assignment operator
    ~Item();                           // Destructor

    // Static method to generate an item
    static Item GenerateItem(unsigned level);

private:
    ItemType type;
    std::string name;
    unsigned power;
};