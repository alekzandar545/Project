#if !TEST_IN_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#else
#define DOCTEST_CONFIG_DISABLE
#endif
#include "doctest.h"

#include "../src/Items/item.h"

// Item Tests
TEST_CASE("Item::ConstructorAndGetters") {
    Item item("Sword", Item::ItemType::Weapon, 100);
    CHECK(item.GetName() == "Sword");
    CHECK(item.GetType() == Item::ItemType::Weapon);
    CHECK(item.GetPower() == 100);
}

TEST_CASE("Item::CopyConstructorAndAssignment") {
    Item item1("Sword", Item::ItemType::Weapon, 100);
    Item item2 = item1; // Copy constructor
    CHECK(item2.GetName() == "Sword");
    CHECK(item2.GetType() == Item::ItemType::Weapon);
    CHECK(item2.GetPower() == 100);

    Item item3;
    item3 = item1; // Assignment operator
    CHECK(item3.GetName() == "Sword");
    CHECK(item3.GetType() == Item::ItemType::Weapon);
    CHECK(item3.GetPower() == 100);
}

TEST_CASE("Item::GenerateItem") {
    Item item = Item::GenerateItem(5);
    CHECK(item.GetPower() >= 20);
    CHECK(item.GetPower() <= 75);
}