#pragma once

#include <iostream>
#include "selectionUI.h"
#include "../Entities/player.h"
#include "../Utils/constants.h"

static const COORD INVENTORY_MENU_SELECT_COORDINATES = {0, 0};

/**
 * @brief The InventoryUI class represents the user interface for displaying and managing the inventory.
 * 
 * It inherits from the SelectionUI class and provides functionality for rendering the inventory, 
 * moving the selection, and checking the selected item.
 */
class InventoryUI : public SelectionUI {
public:
    /**
     * @brief Default constructor for the InventoryUI class.
     */
    InventoryUI();

    /**
     * @brief Copy constructor for the InventoryUI class.
     * 
     * @param other The InventoryUI object to be copied.
     */
    InventoryUI(const InventoryUI& other) = default;

    InventoryUI& operator=(const InventoryUI& other) = default;

    /**
     * @brief Default destructor for the InventoryUI class.
     */
    ~InventoryUI() override = default;

    /**
     * @brief Renders the inventory UI.
     */
    void Render() const override;

    /**
     * @brief Moves the selection in the inventory UI.
     * 
     * @param direction The direction in which to move the selection. True for forward, false for backward.
     */
    void MoveSelection(bool direction) override;

    /**
     * @brief Checks the selected item in the inventory UI.
     */
    void CheckSelection();

private:
    /**
     * @brief Renders the equipped items in the inventory UI.
     */
    void RenderEquippedItems() const;

    /**
     * @brief Displays the details of a specific item in the inventory UI.
     * 
     * @param item The item to be displayed.
     */
    void DisplayItem(const Item& item) const;

    unsigned capacity; /**< The capacity of the inventory. */
};