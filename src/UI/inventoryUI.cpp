#include "inventoryUI.h"
#include "../Utils/gameState.h"

InventoryUI::InventoryUI() 
: SelectionUI(INVENTORY_MENU_SELECT_COORDINATES), capacity(Constants::INVENTORY_CAPACITY){}

void InventoryUI::Render() const {
    const unsigned ConsoleYOffset = 5; // need 5 lines for equipped items to be displayed:
    RenderEquippedItems();

    std::cout << '(' << GameState::GetGamePlayer()->GetInventory().size() << '/' << GameState::GetGamePlayer()->GetInventoryCapacity() << ") " << "Inventory:\n";
    for (size_t i = 0; i < GameState::GetGamePlayer()->GetInventory().size(); i++) {
        SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, (short)(CONSOLE_COORDS.Y + i + ConsoleYOffset)});
        //need to know if item is selected
        if (i == selectionIndex) {
            SetConsoleTextAttribute(CURR_HANDLE, Constants::SELECTED_COLOR);
        }
        DisplayItem(GameState::GetGamePlayer()->GetInventory()[i]);
        if (i == selectionIndex) {
            SetConsoleTextAttribute(CURR_HANDLE, Constants::DEFAULT_COLOR);
        }
    }
    std::cout << "\nPress E to equip item\nPress X to sell item";
}

void InventoryUI::MoveSelection(bool direction) {
    if (direction && selectionIndex < GameState::GetGamePlayer()->GetInventory().size() - 1) {
        selectionIndex++;
        Render();
    } else if (!direction && selectionIndex > 0) {
        selectionIndex--;
        Render();
    }
}

void InventoryUI::CheckSelection() {
    if (selectionIndex == GameState::GetGamePlayer()->GetInventory().size())
        selectionIndex--;
}


void InventoryUI::RenderEquippedItems() const {
    SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, CONSOLE_COORDS.Y});
    std::cout << "Items:\n";
    DisplayItem(GameState::GetGamePlayer()->GetWeapon());
    DisplayItem(GameState::GetGamePlayer()->GetSpell());
    DisplayItem(GameState::GetGamePlayer()->GetArmorPiece());
}

void InventoryUI::DisplayItem(const Item& item) const {
    std::cout << ' ' << item.GetName();
    switch (item.GetType()) {
        case Item::ItemType::Armor:
            std::cout << "(Armor)";
            std::cout << ": " << item.GetPower() << "% dmg reduction";
            break;
        case Item::ItemType::Weapon:
            std::cout << "(Weapon)";
            std::cout << ": " << item.GetPower() << "% melee dmg bonus";
            break;
        case Item::ItemType::Spell:
            std::cout << "(Spell)";
            std::cout << ": " << item.GetPower() << "% magic dmg bonus";
            break;
        case Item::ItemType::Potion:
            std::cout << ": restores 50% HP";
            break;
    }
    std::cout << Constants::padding << '\n';
}
