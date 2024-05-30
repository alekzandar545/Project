#pragma once

#include <vector>
#include "../MapGenerator/map.h"
#include "../Utils/constants.h"
#include "../UI/battleUI.h"
#include "../Entities/player.h"
#include "../Entities/monster.h"



class Event{
private:
    Map* map;
public:
    //constructor
    Event(Map* map);
    //handling cases in combat
    void HandleMeleeAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead);
    void HandleSpellAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead);
    void HandlePotionUsage(BattleUI& ui);
    void HandleFlee(BattleUI& ui, bool& fled);

    //events
    void TreasureEvent();
    void Alert(std::ostringstream& msg) const;
    void BattleAlert(std::ostringstream& msg) const;
    void GameOver() const;
    void MonsterAttack(Player* player, Monster* monster, bool& playerIsDead);
    void MonsterEvent();
    void NextFloor();
};

