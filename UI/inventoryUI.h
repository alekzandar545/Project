#pragma once

#include <iostream>
#include "selectionUI.h"
#include "../Entities/player.h"
#include "../Utils/constants.h"

static const COORD INVENTORY_MENU_SELECT_COORDINATES = {0, 0};

class InventoryUI : public SelectionUI {
public:
    //constructor
    InventoryUI(Player* player);
    //functionality
    void Render() const override;
    void MoveSelection(bool direction) override;
    void CheckSelection();
    //getter
    Player* GetPlayer() const;

private:
    void RenderEquippedItems() const;
    void DisplayItem(const Item& item) const;

    unsigned capacity;
    Player* player;
};