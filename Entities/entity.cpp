#include "entity.h"

bool Entity::TakeHit(unsigned dmg) {
    HP -= dmg - dmg * armor / 100;
    if (HP <= 0) {
        HP = 0;
        return true; // dead
    }
    return false; // not dead
}

void Entity::Heal(unsigned value) {
    if (value + HP > maxHP) {
        HP = maxHP;
    } else {
        HP += value;
    }
}
//getters
unsigned Entity::GetStrength() const {
    return this->str;
}
unsigned Entity::GetMana() const {
    return this->mana;
}
unsigned Entity::GetMaxHP() const {
    return this->maxHP;
}
int Entity::GetHP() const {
    return this->HP;
}
unsigned Entity::GetArmor() const {
    return this->armor;
}
unsigned Entity::GetDexterity() const {
    return this->dexterity;
}

//setters
void Entity::SetStrength(const unsigned value) {
    this->str = value;
}

void Entity::SetMana(const unsigned value) {
    this->mana = value;
}

void Entity::SetMaxHP(const unsigned value) {
    this->maxHP = value;
}

void Entity::SetHP(const int value) {
    this->HP = value;
}

void Entity::SetArmor(const unsigned value) {
    this->armor = value;
}

void Entity::SetDexterity(const unsigned value) {
    this->dexterity = value;
}