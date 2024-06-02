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
    Player(PlayerRace race, const std::string name);
    Player(const std::string name, const unsigned str, const unsigned mana, const unsigned maxHP, const int HP, const unsigned armor, const unsigned dexterity,
        const unsigned statPoints, const unsigned level, const unsigned xp, const unsigned requiredXp, const unsigned gold,
        const std::vector<Item> inventory, const Item& weapon, const Item& spell, const Item& armorPiece){
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
    void EquipItem(const unsigned index){
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
        case Item::ItemType::Potion:
            this->UsePotion(index);
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
    void AddPotion(){
        Item potion("Potion", Item::ItemType::Potion, 50);//potion restores 50% of hp
        inventory.push_back(potion);
    }
    //if used in combat
    bool UsePotion(){
        for(size_t i = 0; i < inventory.size(); i++){
            if(inventory[i].GetType() == Item::ItemType::Potion){
                Heal(maxHP/2);
                inventory.erase(inventory.begin() + i);
                return true;
            }
        }
        return false;
    }
    //if used in inventory
    void UsePotion(unsigned index){
        Heal(maxHP/2);
        inventory.erase(inventory.begin() + index);
    }

    //Getters
    std::string GetName() const;
    unsigned GetStatPoints() const;
    unsigned GetLevel() const;
    unsigned GetXP() const;
    unsigned GetRequiredXP() const;
    unsigned GetGold() const;
    unsigned GetInventorySize() const;
    std::vector<Item> GetInventory() const;
    Item GetWeapon() const;
    Item GetSpell() const;
    Item GetArmorPiece() const;
    unsigned GetInventoryCapacity() const;
    
    //Setters
    void SetName(const std::string& name);
    void SetStatPoints(const unsigned statPoints);
    void SetLevel(const unsigned level);
    void SetXP(const unsigned xp);
    void SetRequiredXP(const unsigned requiredXp);
    void SetGold(const unsigned gold);
    void SetInventory(const std::vector<Item>& inventory);
    void SetWeapon(const Item& weapon);
    void SetSpell(const Item& spell);
    void SetArmorPiece(const Item& armorPiece);
    
private:
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
