#pragma once
#include <iostream>
#include "selectionUI.h"
#include "../Entities/player.h"

static const COORD STATS_SELECT_COORDINATES = {0, 0};
//maybe singleton?
class StatsUI : public SelectionUI{
public:
    StatsUI(Player player) : SelectionUI(STATS_SELECT_COORDINATES){
        this->player = &player;
    }
    
private:
    Player* player;
};
