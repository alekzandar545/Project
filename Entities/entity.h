#pragma once

class Entity{
public:
    bool TakeHit(unsigned dmg){
        HP -= dmg - dmg*armor/100;
        if(HP <= 0){
            HP = 0;
            return 1; //dead
        }
        return 0; //not dead
    }
    unsigned GetStrength() const{return this->str;}
    unsigned GetMana() const {return this->mana;}
    unsigned GetMaxHP() const {return this->maxHP;}
    int GetHP() const {return this->HP;}
    unsigned GetArmor() const {return this->armor;}
    unsigned GetDexterity() const {return this->dexterity;}
//public:
    unsigned str;
    unsigned mana;
    unsigned maxHP;
    int HP;
    unsigned armor;
    unsigned dexterity;
};