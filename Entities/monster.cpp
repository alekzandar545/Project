#include "monster.h"

Monster::Monster(unsigned level){
    //at level(floor) 0 no extra stats
    this->level = level;
    maxHP = 50 + 10*level;
    mana = 25 + 10*level;
    str = 25 + 10*level;
    armor = 15 + 5*level;
    dexterity = 10 + 5*level;
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
    unsigned dmg = ChooseAttack(attack) - rand() % 5*level;//nerfed the dmg a bit
    return pl->TakeHit(dmg);
}