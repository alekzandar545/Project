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
        Sorcerer
    };
    //constructors
    Player(PlayerRace race, std::string name);
    //leveling
    void LevelUp();
    void AddXP(unsigned xp);
    //combat
    bool MeleeAttack(Monster& monster) const;
    bool SpellAttack(Monster& monster) const;
    //item management
    void EquipItem(unsigned index){//index will be decided from ui placement
        Item newItem = inventory[index]; //create a copy
        switch (inventory[index].GetType())
        {
        case Item::ItemType::Weapon:
            inventory[index] = this->weapon;
            this->weapon = newItem;
            break;
        case Item::ItemType::Spell:
            inventory[index] = this->spell;
            this->spell = newItem;
            break;
        case Item::ItemType::Armor:
            this->armor -= this->armorPiece.GetPower();
            inventory[index] = this->armorPiece;
            this->armorPiece = newItem;
            this->armor += this->armorPiece.GetPower();
            break;
        }
    }
    //inventory
    void AddItem(Item item){
        inventory.push_back(item);
    }
    void AddGold(const unsigned gold){
        this->gold+=gold;
    }
    //stats
    void AddStrength(){
        if(statPoints > 0){
            str++;
            statPoints--;
        }
    }
    void AddMana(){
        if(statPoints > 0){
            mana++;
            statPoints--;
        }
    }
    void AddHP(){
       if(statPoints > 0){
            maxHP++;
            HP++;
            statPoints--;
       } 
    }
    void AddDexterity(){
        if(statPoints > 0){
            dexterity++;
            statPoints--;
        }
    }

    //getters
    std::string GetName() const{return this->name;}
//private:
    unsigned statPoints;
    unsigned level;
    unsigned xp;
    unsigned requiredXp;
    unsigned gold;
    std::string name;
    std::vector<Item> inventory;
    Item spell;
    Item weapon;
    Item armorPiece;

};