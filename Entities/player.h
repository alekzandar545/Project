#pragma once
#include "entity.h"
#include "monster.h"
#include "../Items/item.h"
#include <vector>

class Monster; //forward declaration

class Player : public Entity{
public:
    enum class PlayerRace{
        Human,
        Berserk,
        Sorcerrer
    };
    Player(PlayerRace race);
    //leveling
    void LevelUp();
    void SetXp(unsigned xp);
    //combat
    void MeleeAttack(Monster& monster) const;
    void SpellAttack(Monster& monster) const;
    //item management
    void EquipItem(unsigned index){//index will be decided from ui placement
        Item* newItem = &inventory[index];
        switch (inventory[index].GetType())
        {
        case Item::ItemType::Weapon:
            inventory[index] = this->weapon;
            this->weapon = *newItem;
            break;
        case Item::ItemType::Spell:
            inventory[index] = this->spell;
            this->spell = *newItem;
            break;
        case Item::ItemType::Armor:
            this->armor -= this->armorPiece.GetPower();
            inventory[index] = this->armorPiece;
            this->armorPiece = *newItem;
            this->armor += this->armorPiece.GetPower();
            break;
        }
    }
    void AddItem(Item item){
        inventory.push_back(item);
    }
//private:
    unsigned level;
    unsigned xp;
    unsigned requiredXp;
    unsigned gold;
    std::vector<Item> inventory;
    Item spell;
    Item weapon;
    Item armorPiece;

};