#include "player.h"

//constructors
Player::Player(PlayerRace race, std::string name) : gold(0), xp(0), level(1), requiredXp(100){
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
    this->weapon = Item("Shortsword", Item::ItemType::Weapon, 20);
    this->spell = Item("Fireball", Item::ItemType::Spell, 20);
    this->name = name;
};
//leveling
void Player::LevelUp(){
    level++;
    unsigned leftoverXP = this->xp % requiredXp;
    xp = leftoverXP;
    requiredXp += requiredXp/10; //lets see if this progression is too slow
    HP = maxHP;
}

void Player::AddXP(unsigned xp){
    this->xp += xp;
    if(this->xp >= requiredXp)
        LevelUp();
}
//combat
bool Player::MeleeAttack(Monster& monster) const{
    return monster.TakeHit(str + weapon.GetPower());
}
bool Player::SpellAttack(Monster& monster) const{
    return monster.TakeHit(mana + spell.GetPower());
}
