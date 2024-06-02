#pragma once

class Entity {
public:
    bool TakeHit(const unsigned dmg);
    void Heal(const unsigned value);
    //getters
    unsigned GetStrength() const;
    unsigned GetMana() const;
    unsigned GetMaxHP() const;
    int GetHP() const;
    unsigned GetArmor() const;
    unsigned GetDexterity() const;
    //setters
    void SetStrength(const unsigned value);
    void SetMana(const unsigned value);
    void SetMaxHP(const unsigned value);
    void SetHP(const int value);
    void SetArmor(const unsigned value);
    void SetDexterity(const unsigned value);
    
protected:
    unsigned str;
    unsigned mana;
    unsigned maxHP;
    int HP;
    unsigned armor;
    unsigned dexterity;
};;;