#pragma once
#include "entity.h"
#include "player.h"


class Monster : public Entity{
public:
    enum class Attacks{
        MeleeAttack,
        SpellAttack
    };
    //constructors
    Monster();
    Monster(unsigned level);
    //combat
    unsigned ChooseAttack(Attacks& attack) const;
    bool Attack(Entity* pl, Attacks& attack) const;
private:
    unsigned level;
};
