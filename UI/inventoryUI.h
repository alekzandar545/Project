#pragma once
#include <iostream>
#include "selectionUI.h"
#include "../Entities/player.h"
static const COORD SELECT_COORDINATES = {1, 1};
//maybe singleton?
class InventoryUI : public SelectionUI{
public:
    InventoryUI(COORD coords, Player player) : SelectionUI(SELECT_COORDINATES){
        for (size_t i = 0; i < player.inventory.size(); i++)
        {
            AddOption(player.inventory[i].GetName());
        }
    }
private:
};
