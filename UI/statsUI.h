#pragma once
#include "selectionUI.h"
#include "../Entities/player.h"
#include <windows.h>
#include <iostream>



class StatsUI : public SelectionUI {
public:
    StatsUI(Player* player);
    void Render() const override;
    Player* GetPlayer() const;

private:
    static const COORD STATS_SELECT_COORDINATES;
    Player* player;
};