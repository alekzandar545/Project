#pragma once

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
    //events
    void TreasureEvent();
    void GameOver() const;
    void MonsterAttack(Player* player, Monster* monster, bool& playerIsDead);
    void MonsterEvent();
    void NextFloor();
};

