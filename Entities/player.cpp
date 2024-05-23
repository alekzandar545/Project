#include "player.h"

//constructors
Player::Player(PlayerRace race) : gold(0), xp(0), level(1), requiredXp(100){
    switch (race)
    {
    case PlayerRace::Human:
        this->str = 30;
        this->mana = 20;
        break;
    case PlayerRace::Berserk:
        this->str = 40;
        this->mana = 10;
        break;
    case PlayerRace::Sorcerrer:
        this->str = 10;
        this->mana = 40;
        break;        
    }
    this->armor = 0;
    this->maxHP = 50;
    this->HP = 50;
};
//leveling
void Player::LevelUp(){
    level++;
    xp = 0;
    requiredXp += requiredXp/10; //lets see if this progression is too slow
    HP = maxHP;
}

void Player::SetXp(unsigned xp){
    this->xp += xp;
    if(this->xp >= requiredXp)
        LevelUp();
}
//combat
void Player::MeleeAttack(Monster& monster) const{
    monster.TakeHit(str + weapon.GetPower());
}
void Player::SpellAttack(Monster& monster) const{
    monster.TakeHit(mana + spell.GetPower());
}
