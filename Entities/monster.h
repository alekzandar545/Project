#pragma once
#include "entity.h"
#include "player.h"

class Monster : public Entity{
public:
    Monster(unsigned level);
    //combat
    unsigned ChooseAttack() const;
    void Attack(Entity* pl) const;
private:
};
