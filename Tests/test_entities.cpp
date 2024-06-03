#if !TEST_IN_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#else
#define DOCTEST_CONFIG_DISABLE
#endif
#include "doctest.h"

#include "../src/Entities/entity.h"
#include "../src/Entities/monster.h"
#include "../src/Entities/player.h"

#include <string>
#include <vector>

// Entity Tests
TEST_CASE("Entity::TakeHit") {
    Entity e;
    e.SetMaxHP(100);
    e.SetHP(100);
    e.SetArmor(20);
    
    SUBCASE("Entity survives hit") {
        CHECK(e.TakeHit(50) == false); // 50 - 20% of 50 = 40 damage
        CHECK(e.GetHP() == 60);
    }
    SUBCASE("Entity dies from hit") {
        CHECK(e.TakeHit(200) == true); // 200 - 20% of 200 = 160 damage
        CHECK(e.GetHP() == 0);
    }
}

TEST_CASE("Entity::Heal") {
    Entity e;
    e.SetMaxHP(100);
    e.SetHP(50);
    
    SUBCASE("Healing without exceeding max HP") {
        e.Heal(30);
        CHECK(e.GetHP() == 80);
    }
    
    SUBCASE("Healing with exceeding max HP") {
        e.Heal(60);
        CHECK(e.GetHP() == 100);
    }
}

TEST_CASE("Entity::GettersAndSetters") {
    Entity e;
    e.SetStrength(20);
    e.SetMana(30);
    e.SetMaxHP(150);
    e.SetHP(100);
    e.SetArmor(25);
    e.SetDexterity(15);

    CHECK(e.GetStrength() == 20);
    CHECK(e.GetMana() == 30);
    CHECK(e.GetMaxHP() == 150);
    CHECK(e.GetHP() == 100);
    CHECK(e.GetArmor() == 25);
    CHECK(e.GetDexterity() == 15);
}

// Monster Tests
TEST_CASE("Monster::Constructor") {
    Monster m1(3);
    CHECK(m1.GetMaxHP() == 70); // 50 + 10*(3-1)
    CHECK(m1.GetMana() == 45);  // 25 + 10*(3-1)
    CHECK(m1.GetStrength() == 45); // 25 + 10*(3-1)
    CHECK(m1.GetArmor() == 25); // 15 + 5*(3-1)
    CHECK(m1.GetDexterity() == 20); // 10 + 5*(3-1)
    CHECK(m1.GetHP() == 70);

    Monster m2;
    CHECK(m2.GetMaxHP() == 50);
    CHECK(m2.GetMana() == 25);
    CHECK(m2.GetStrength() == 25);
    CHECK(m2.GetArmor() == 15);
    CHECK(m2.GetDexterity() == 10);
    CHECK(m2.GetHP() == 50);
}

TEST_CASE("Monster::ChooseAttack") {
    Monster m;
    Monster::Attacks attack;

    unsigned attackPower = m.ChooseAttack(attack);
    CHECK((attack == Monster::Attacks::MeleeAttack || attack == Monster::Attacks::SpellAttack));
    if (attack == Monster::Attacks::MeleeAttack) {
        CHECK(attackPower == m.GetStrength());
    } else {
        CHECK(attackPower == m.GetMana());
    }
}

TEST_CASE("Monster::Attack") {
    Monster m;
    Entity e;
    e.SetMaxHP(100);
    e.SetHP(100);
    e.SetArmor(0);

    Monster::Attacks attack;
    bool isDead = m.Attack(&e, attack);
    CHECK(isDead == false);
    CHECK(e.GetHP() < 100);
}

// Player Tests
TEST_CASE("Player::Constructors") {
    Player p1;
    CHECK(p1.GetStrength() == 30);
    CHECK(p1.GetMana() == 20);

    Player p2(Player::PlayerRace::Berserk, "Berserk");
    CHECK(p2.GetStrength() == 40);
    CHECK(p2.GetMana() == 10);

    Player p3(Player::PlayerRace::Sorcerer, "Sorcerer");
    CHECK(p3.GetStrength() == 10);
    CHECK(p3.GetMana() == 40);

    Player p4(p2); // Copy constructor
    CHECK(p4.GetStrength() == 40);
    CHECK(p4.GetMana() == 10);

    Player p5;
    p5 = p3; // Assignment operator
    CHECK(p5.GetStrength() == 10);
    CHECK(p5.GetMana() == 40);
}

TEST_CASE("Player::LevelUp") {
    Player p;
    p.AddXP(0);
    unsigned initialStatPoints = p.GetStatPoints();
    p.LevelUp();
    CHECK(p.GetLevel() == 2);
    CHECK(p.GetXP() < 1000);
    CHECK(p.GetStatPoints() == initialStatPoints + 30);
}

TEST_CASE("Player::Combat") {
    Player p;
    Monster m;

    CHECK(p.MeleeAttack(m) == false);
    CHECK(m.GetHP() < m.GetMaxHP());
    m.SetHP(m.GetMaxHP());
    p.SetHP(p.GetMaxHP());
    CHECK(p.SpellAttack(m) == false);
    CHECK(m.GetHP() < m.GetMaxHP());
}

TEST_CASE("Player::GettersAndSetters") {
    Player p;
    p.SetName("Hero");
    p.SetStatPoints(5);
    p.SetLevel(2);
    p.SetXP(500);
    p.SetRequiredXP(1000);
    p.SetGold(100);
    p.SetWeapon(Item("Sword", Item::ItemType::Weapon, 30));
    p.SetSpell(Item("IceBlast", Item::ItemType::Spell, 25));
    p.SetArmorPiece(Item("Chainmail", Item::ItemType::Armor, 20));
    
    CHECK(p.GetName() == "Hero");
    CHECK(p.GetStatPoints() == 5);
    CHECK(p.GetLevel() == 2);
    CHECK(p.GetXP() == 500);
    CHECK(p.GetRequiredXP() == 1000);
    CHECK(p.GetGold() == 100);
    CHECK(p.GetWeapon().GetName() == "Sword");
    CHECK(p.GetSpell().GetName() == "IceBlast");
    CHECK(p.GetArmorPiece().GetName() == "Chainmail");
}
