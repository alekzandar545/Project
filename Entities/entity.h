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
//public:
    unsigned str;
    unsigned mana;
    unsigned maxHP;
    int HP;
    unsigned armor;
};