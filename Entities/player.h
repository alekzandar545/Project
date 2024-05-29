#pragma once
#include "entity.h"
#include "monster.h"
#include "../Items/item.h"
#include <vector>
#include <stdexcept>

class Monster; //forward declaration

class Player : public Entity{
public:
    enum class PlayerRace{
        Human,
        Berserk,
        Sorcerer
    };
    //constructors
    Player();
    Player(PlayerRace race, std::string name);
    Player(std::string name, unsigned str, unsigned mana, unsigned maxHP, int HP, unsigned armor, unsigned dexterity,
        unsigned statPoints, unsigned level, unsigned xp, unsigned requiredXp, unsigned gold,
        std::vector<Item> inventory, const Item& weapon, const Item& spell, const Item& armorPiece){
            inventoryCapacity = 10;
            this->name = name;
            this->str = str;
            this->mana = mana;
            this->maxHP = maxHP;
            this->HP = HP;
            this->armor = armor;
            this->dexterity = dexterity;
            this->statPoints = statPoints;
            this->level = level;
            this->xp = xp;
            this->requiredXp = requiredXp;
            this->gold = gold;
            this->inventory = inventory;
            this->weapon = weapon;
            this->spell = spell;
            this->armorPiece = armorPiece;
        }
    //leveling
    void LevelUp();
    void AddXP(unsigned xp);
    //combat
    bool MeleeAttack(Monster& monster) const;
    bool SpellAttack(Monster& monster) const;
    //item management
    void EquipItem(const unsigned index){//index will be decided from ui placement
        if (this->inventory.size() == 0) 
            throw std::out_of_range("Cannot equip item: Inventory is empty.");
        if (index >= this->inventory.size())
            throw std::out_of_range("Cannot equip item: Index is out of range.");
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
    bool AddItem(const Item& item){
        if(this->inventory.size() < this->inventoryCapacity){
            this->inventory.push_back(item);
            return 1; //success
        }
        return 0; //failed
    }

    void SellItem(const unsigned index){
        if (this->inventory.size() == 0) 
            throw std::out_of_range("Cannot sell item: Inventory is empty.");
        if (index >= this->inventory.size())
            throw std::out_of_range("Cannot sell item: Index is out of range.");
        this->gold += inventory[index].GetPower()/2;
        this->inventory.erase(this->inventory.begin() + index);
    }
    //gold
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

    //Getters
    std::string GetName() const{return this->name;}
    unsigned GetStatPoints() const {return this->statPoints;}
    unsigned GetLevel() const {return this->level;}
    unsigned GetXP() const {return this->xp;}
    unsigned GetRequiredXP() const {return this->requiredXp;}
    unsigned GetGold() const {return this->gold;}
    unsigned GetInventorySize() const {return this->inventory.size();}
    std::vector<Item> GetInventory() const {return this->inventory;}
    Item GetWeapon() const {return this->weapon;}
    Item GetSpell() const {return this->spell;}
    Item GetArmorPiece() const {return this->armorPiece;}
//private:
    unsigned inventoryCapacity;
    unsigned statPoints;
    unsigned level;
    unsigned xp;
    unsigned requiredXp;
    unsigned gold;
    std::string name;
    std::vector<Item> inventory;
    Item weapon;
    Item spell;
    Item armorPiece;

};