#if !TEST_IN_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#else
#define DOCTEST_CONFIG_DISABLE
#endif
#include "doctest.h"

#include "../src/Utils/gameLoader.h"
#include "../src/Utils/gameSaver.h"
#include "../src/Entities/player.h"

#include <chrono>
#include <ctime>

// Mock classes for Player and Map to test GameLoader and GameSaver
class MockPlayer : public Player {
public:
    std::string GetName() const;
    unsigned GetStrength() const;
    unsigned GetMana() const;
    unsigned GetMaxHP() const;
    int GetHP() const;
    unsigned GetArmor() const;
    unsigned GetDexterity() const;
    unsigned GetStatPoints() const;
    unsigned GetLevel() const;
    unsigned GetXP() const;
    unsigned GetRequiredXP() const;
    unsigned GetGold() const;
    unsigned GetInventorySize() const;
    std::vector<Item> GetInventory() const;
    Item GetWeapon() const;
    Item GetSpell() const;
    Item GetArmorPiece() const;
};;

class MockMap : public Map {
public:
    unsigned GetWidth() const;
    unsigned GetHeight() const;
    unsigned GetPlayerX() const;
    unsigned GetPlayerY() const;
    unsigned GetMonsterCount() const;
    unsigned GetTreasureCount() const;
    unsigned GetFloor() const;
    std::vector<std::vector<char>> GetMatrix() const;
};

// GameLoader Tests
TEST_CASE("GameLoader::LoadGame") {
    MockPlayer player;
    MockMap map;
    GameLoader loader;
    std::string saveFile = "testSaveFile.bin";

    CHECK_THROWS_AS(loader.LoadGame(player, map, saveFile), std::runtime_error);
}

TEST_CASE("GameLoader::DisplayHighScores") {
    GameLoader loader;
    CHECK_NOTHROW(loader.DisplayHighScores());
}

// GameSaver Tests
TEST_CASE("GameSaver::SaveGame") {
    MockPlayer player;
    MockMap map;
    GameSaver saver;
    std::string dir = "testSaveDir/";

    CHECK_THROWS_AS(saver.SaveGame(player, map, dir), std::runtime_error);
}

TEST_CASE("GameSaver::SaveHighscore") {
    MockPlayer player;
    GameSaver saver;
    std::string dir = "testSaveDir/";

    CHECK_THROWS_AS(saver.SaveHighscore(player, dir), std::runtime_error);
}


