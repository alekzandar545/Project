#include "monster.h"

Monster::Monster(unsigned level){
    //at level(floor) 0 no extra stats
    maxHP = 50 + 10*level;
    mana = 25 + 10*level;
    str = 25 + 10*level;
    armor = 15 + 5*level;
    dexterity = 10 + 10*level;
    HP = maxHP;
}
//combat
unsigned Monster::ChooseAttack(Attacks& attack) const{ //chooses either a str or mana atk
    bool MeleeAtk = rand() % 2;
    if(MeleeAtk){
        attack = Attacks::MeleeAttack;
        return str;
    }
    attack = Attacks::SpellAttack;
    return mana;
    
}
bool Monster::Attack(Entity* pl, Attacks& attack) const{
    return pl->TakeHit(ChooseAttack(attack));
}