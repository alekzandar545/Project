#pragma once
#include "selectionUI.h"
#include "../Entities/player.h"
#include <windows.h>
#include <iostream>



class StatsUI : public SelectionUI {
public:
    //constructors
    StatsUI();
    StatsUI(const StatsUI& other) = default;
    ~StatsUI() = default;
    //shouldn't delete pointer to player, because UI only displays it, dosnt really own it

    void Render() const override;

private:
    static const COORD STATS_SELECT_COORDINATES;
};