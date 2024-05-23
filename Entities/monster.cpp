#include "monster.h"

Monster::Monster(unsigned level){
    //at level 1 no extra stats
    maxHP = 50 + 10*(level-1);
    mana = 25 + 10*(level-1);
    str = 25 + 10*(level-1);
    armor = 15 + 5*(level-1);
    HP = maxHP;
}
//combat
unsigned Monster::ChooseAttack() const{ //chooses either a str or mana atk
    bool MeleeAtk = rand() % 2;
    if(MeleeAtk)
        return str;
    return mana;
    
}
void Monster::Attack(Entity* pl) const{
    pl->TakeHit(ChooseAttack());
}