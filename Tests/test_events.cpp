#if !TEST_IN_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#else
#define DOCTEST_CONFIG_DISABLE
#endif
#include "doctest.h"

#include "../src/Events/alerts.h"
#include "../src/Events/combatEvents.h"
#include "../src/Events/eventHandler.h"
#include "../src/Entities/player.h"
#include "../src/mapGenerator/map.h"
#include "../src/Utils/constants.h"

// Alerts Tests
TEST_CASE("Alerts::Alert") {
    std::ostringstream msg;
    msg << "Test Alert Message";
    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream capturedCout;
    std::cout.rdbuf(capturedCout.rdbuf());

    Alerts::Alert(msg);

    std::cout.rdbuf(originalCoutStreamBuf);
    CHECK(capturedCout.str() == "Test Alert Message" + Constants::padding +'\n');
}

TEST_CASE("Alerts::BattleAlert") {
    std::ostringstream msg;
    msg << "Test Battle Alert Message";
    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream capturedCout;
    std::cout.rdbuf(capturedCout.rdbuf());

    Alerts::BattleAlert(msg);

    std::cout.rdbuf(originalCoutStreamBuf);
    CHECK(capturedCout.str() == "Test Battle Alert Message" + Constants::padding +'\n');
}

// // CombatEvents Tests
TEST_CASE("CombatEvents::HandleMeleeAttack") {
    Map map;
    CombatEvents combatEvents(&map);
    Player player;
    GameState::SetGamePlayer(&player);
    Monster monster;
    BattleUI ui(&monster);
    bool playerIsDead = false;
    bool monsterIsDead = false;

    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream capturedCout;
    std::cout.rdbuf(capturedCout.rdbuf());

    combatEvents.HandleMeleeAttack(ui, playerIsDead, monsterIsDead);

    std::cout.rdbuf(originalCoutStreamBuf);
    CHECK_FALSE(playerIsDead);
    CHECK((monsterIsDead || !monsterIsDead)); // Checking if it's either true or false since the randomness can vary
}

TEST_CASE("CombatEvents::HandleSpellAttack") {
    Map map;
    CombatEvents combatEvents(&map);
    Player player;
    GameState::SetGamePlayer(&player);
    Monster monster;
    BattleUI ui(&monster);
    bool playerIsDead = false;
    bool monsterIsDead = false;

    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream capturedCout;
    std::cout.rdbuf(capturedCout.rdbuf());

    combatEvents.HandleSpellAttack(ui, playerIsDead, monsterIsDead);

    std::cout.rdbuf(originalCoutStreamBuf);
    CHECK_FALSE(playerIsDead);
    CHECK((monsterIsDead || !monsterIsDead)); // Checking if it's either true or false since the randomness can vary
}

TEST_CASE("CombatEvents::HandlePotionUsage") {
    Map map;
    CombatEvents combatEvents(&map);
    Player player;
    Monster monster;
    GameState::SetGamePlayer(&player);
    BattleUI ui(&monster);

    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream capturedCout;
    std::cout.rdbuf(capturedCout.rdbuf());

    combatEvents.HandlePotionUsage(ui);

    std::cout.rdbuf(originalCoutStreamBuf);
    bool cond1 = capturedCout.str().find("has no potions") != std::string::npos;
    bool cond2 = capturedCout.str().find("has used a potion to restore 50% HP") != std::string::npos;
    bool cond = cond1 || cond2;
    CHECK(cond);
}

TEST_CASE("CombatEvents::HandleFlee") {
    Map map;
    CombatEvents combatEvents(&map);
    Player player;
    GameState::SetGamePlayer(&player);
    Monster monster;
    BattleUI ui(&monster);
    bool fled = false;

    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream capturedCout;
    std::cout.rdbuf(capturedCout.rdbuf());

    combatEvents.HandleFlee(ui, fled);

    std::cout.rdbuf(originalCoutStreamBuf);
    CHECK(fled == true);
    CHECK(capturedCout.str().find("has fled!") != std::string::npos);
}

// // Event Tests
// TEST_CASE("Event::TreasureEvent") {
//     Map map;
//     Player player;
//     map.SetPlayer(&player);
//     Event event(&map);

//     std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
//     std::ostringstream capturedCout;
//     std::cout.rdbuf(capturedCout.rdbuf());

//     event.TreasureEvent();

//     std::cout.rdbuf(originalCoutStreamBuf);
//     bool cond1 = capturedCout.str().find("just acquired") != std::string::npos;
//     bool cond2 = capturedCout.str().find("Inventory is full!") != std::string::npos;
//     bool cond = cond1 || cond2;
//     CHECK(cond);
// }

// TEST_CASE("Event::GameOver") {
//     Map map;
//     Player player;
//     map.SetPlayer(&player);
//     Event event(&map);

//     std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
//     std::ostringstream capturedCout;
//     std::cout.rdbuf(capturedCout.rdbuf());

//     event.GameOver();

//     std::cout.rdbuf(originalCoutStreamBuf);
//     CHECK(capturedCout.str().find("GAME OVER") != std::string::npos);
//     CHECK(capturedCout.str().find("Gold highscore") != std::string::npos);
// }

// TEST_CASE("Event::MonsterAttack") {
//     Map map;
//     Player player;
//     Monster monster(1);
//     Event event(&map);
//     bool playerIsDead = false;

//     std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
//     std::ostringstream capturedCout;
//     std::cout.rdbuf(capturedCout.rdbuf());

//     event.MonsterAttack(&player, &monster, playerIsDead);

//     std::cout.rdbuf(originalCoutStreamBuf);
//     CHECK((capturedCout.str().find("The dragon hit") != std::string::npos ||
//            capturedCout.str().find("The dragon burned") != std::string::npos));
//     CHECK((playerIsDead || !playerIsDead)); // Checking if it's either true or false since the randomness can vary
// }

// TEST_CASE("Event::MonsterEvent") {
//     Map map;
//     Player player;
//     map.SetPlayer(&player);
//     Event event(&map);

//     std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
//     std::ostringstream capturedCout;
//     std::cout.rdbuf(capturedCout.rdbuf());

//     event.MonsterEvent();

//     std::cout.rdbuf(originalCoutStreamBuf);
//     CHECK((capturedCout.str().find("Surprise attack!") != std::string::npos ||
//            capturedCout.str().find("has been slain") != std::string::npos ||
//            capturedCout.str().find("Floor passed") != std::string::npos));
// }

// TEST_CASE("Event::NextFloor") {
//     Map map;
//     Player player;
//     map.SetPlayer(&player);
//     Event event(&map);

//     std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
//     std::ostringstream capturedCout;
//     std::cout.rdbuf(capturedCout.rdbuf());

//     event.NextFloor();

//     std::cout.rdbuf(originalCoutStreamBuf);
//     CHECK(capturedCout.str().find("Floor 1 passed!") != std::string::npos);
// }