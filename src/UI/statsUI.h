#pragma once
#include "selectionUI.h"
#include "../Entities/player.h"
#include <windows.h>
#include <iostream>



/**
 * @class StatsUI
 * @brief Represents the user interface for displaying statistics.
 * 
 * This class inherits from the SelectionUI class and provides functionality
 * for rendering statistics on the screen.
 */
class StatsUI : public SelectionUI {
public:
    //constructors
    StatsUI();
    StatsUI(const StatsUI& other) = default;
    StatsUI& operator=(const StatsUI& other) = default;
    ~StatsUI() override = default;
    //shouldn't delete pointer to player, because UI only displays it, dosnt really own it

    /**
     * @brief Renders the statistics on the screen.
     */
    void Render() const override;

private:
    static const COORD STATS_SELECT_COORDINATES;
};