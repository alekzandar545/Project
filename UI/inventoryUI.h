#pragma once

#include <iostream>
#include "selectionUI.h"
#include "../Entities/player.h"
#include "../constants.h"
static const COORD INVENTORY_MENU_SELECT_COORDINATES = {0, 0};

//maybe singleton?
class InventoryUI : public SelectionUI{
public:
    InventoryUI(Player* player) : SelectionUI(INVENTORY_MENU_SELECT_COORDINATES){
        this->player = player;
        capacity = 10;
    }
    void RenderEquippedItems() const{
        SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, CONSOLE_COORDS.Y});
        std::cout << "Items:\n";
        std::cout << ' ' << player->armorPiece.GetName()<< "(Armor)" << ": " << player->armorPiece.GetPower() << "% dmg reduction" << padding << '\n';
        std::cout << ' ' << player->weapon.GetName()<< "(Weapon)" << ": " << player->weapon.GetPower() << "% melee dmg bonus" << padding << '\n';
        std::cout << ' ' << player->spell.GetName()<< "(Spell)" << ": " << player->spell.GetPower() << "% magic dmg bonus" << padding << '\n';
    }
    void Render() const override{
        const unsigned ConsoleYOffset = 5; // need 5 lines for equipped items to be displayed:
        RenderEquippedItems();

        std::cout <<'(' << player->inventory.size() << '/' << player->inventoryCapacity << ") " << "Inventory:\n";
        for (size_t i = 0; i < player->inventory.size(); i++)
        {
            SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, (short)(CONSOLE_COORDS.Y + i + ConsoleYOffset)});
            if(i==selectionIndex)
                SetConsoleTextAttribute(CURR_HANDLE, 22);
            std::cout << ' ' << player->inventory[i].GetName();
            switch(player->inventory[i].GetType()){
                case Item::ItemType::Armor:
                    std::cout << "(Armor)";
                    std::cout << ": " << player->inventory[i].GetPower() << "% dmg reduction";
                    break;
                case Item::ItemType::Weapon:
                    std::cout << "(Weapon)";
                    std::cout << ": " << player->inventory[i].GetPower() << "% melee dmg bonus";
                    break;
                case Item::ItemType::Spell:
                    std::cout << "(Spell)";
                    std::cout << ": " << player->inventory[i].GetPower() << "% magic dmg bonus";
                    break;
            }
            
            std::cout << padding <<'\n';
            SetConsoleTextAttribute(CURR_HANDLE, 8);
        }
        std::cout << "\nPress E to equip item\nPress X to sell item";
    }

    void MoveSelection(bool direction) override{//goes up for 0 down for 1
        if(direction && selectionIndex < player->inventory.size()-1){
            selectionIndex++;
            Render();
        }
        else if(!direction && selectionIndex > 0){
            selectionIndex--;
            Render();
        }
    }
    //check if item was removed recently
    void CheckSold(){
        if(selectionIndex == player->inventory.size())
            selectionIndex--;
    }
    //getters
    Player* GetPlayer() const{
        return this->player;
    }
private:
    unsigned capacity;
    Player* player;
};
