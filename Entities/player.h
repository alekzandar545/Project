#pragma once
#include "entity.h"
#include "inventory.h"

class Player : Entity{
public:
    enum PlayerRace{
        Human,
        Berserk,
        Sorcerrer
    };
    Player(PlayerRace race){
        switch (race)
        {
        case Human:
            this->hp = 50;
            this->str = 30;
            this->mana = 20;
            return;
        case Berserk:
            this->hp = 50;
            this->str = 40;
            this->mana = 10;
            return;
        case Sorcerrer:
            this->hp = 50;
            this->str = 10;
            this->mana = 40;
            return;        
        }
    };

private:
    unsigned xp;
    unsigned gold;
};