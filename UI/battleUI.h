#pragma once

#include <iostream>
#include "selectionUI.h"
#include "../Entities/player.h"
#include "../Entities/monster.h"
#include "../Utils/constants.h"

static const COORD BATTLE_MENU_SELECT_COORDINATES = {18, 1};
static const unsigned PLAYER_HP_OFFSET = 4;
static const unsigned MONSTER_HP_OFFSET = 53;

class BattleUI : public SelectionUI {
public:
    BattleUI(Player* player, Monster* monster);

    void RenderGraphics() const;
    void Render() const override;
    void RenderHPBars() const;

    Player* getPlayer() const;
    Monster* getMonster() const;

private:
    Player* player;
    Monster* monster;
    std::vector<std::string> playerArt;
    std::vector<std::string> dragonArt;
};