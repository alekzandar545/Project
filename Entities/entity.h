#pragma once

class Entity{
public:
    void TakeHit(unsigned dmg){
        maxHP -= dmg - dmg*armor;
    }
//public:
    unsigned str;
    unsigned mana;
    unsigned maxHP;
    unsigned HP;
    unsigned armor;
};