#pragma once
#include "../UI/battleUI.h"
#include "alerts.h"

class CombatEvents{
public:
    //construction
    CombatEvents(Map* map);
    //handling cases in combat
    void DropPotion(Player& player);
    void HandleMeleeAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead);
    void HandleSpellAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead);
    void HandlePotionUsage(BattleUI& ui);
    void HandleFlee(BattleUI& ui, bool& fled);
private:
    Map* map;
};