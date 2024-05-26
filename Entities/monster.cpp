#include "monster.h"

Monster::Monster(unsigned level){
    //at level 1 no extra stats
    maxHP = 50 + 10*level;
    mana = 25 + 10*level;
    str = 25 + 10*level;
    armor = 15 + 5*level;
    HP = maxHP;
}
//combat
unsigned Monster::ChooseAttack() const{ //chooses either a str or mana atk
    bool MeleeAtk = rand() % 2;
    if(MeleeAtk)
        return str;
    return mana;
    
}
bool Monster::Attack(Entity* pl) const{
    return pl->TakeHit(ChooseAttack());
}