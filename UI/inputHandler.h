#pragma once

#include "../Entities/player.h"
#include "../UI/inventoryUI.h"
#include "../UI/statsUI.h"
#include "../UI/startMenuUI.h"
#include "../UI/selectionUI.h"
#include "../constants.h"
#include "../Events/eventHandler.h"

class InputHandler {
public:
    InputHandler(Event* event);
    void BattleUserInput(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead, bool& fled);
    static void UserInput(Map& map, Player& p, bool& isGameOver);
    static bool InventoryUserInput(InventoryUI& ui);
    static bool StatsUserInput(StatsUI& ui);
    static void StartUserInput(StartMenuUI& ui, bool& OpenStartUI, bool& isGameOver);
    static void RaceSelectInput(SelectionUI& ui, bool& OpenRaceSelectUI, Player::PlayerRace& race);
private:
    Event* event;
};

