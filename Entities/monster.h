#pragma once
#include "entity.h"
#include "player.h"

class Monster : public Entity{
public:
    Monster(unsigned level);
    //combat
    unsigned ChooseAttack() const;
    bool Attack(Entity* pl) const;
private:
};
