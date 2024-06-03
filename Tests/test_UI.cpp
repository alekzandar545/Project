#if !TEST_IN_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#else
#define DOCTEST_CONFIG_DISABLE
#endif
#include "doctest.h"

#include "../src/UI/selectionUI.h"
#include "../src/UI/startMenuUI.h"
#include "../src/UI/statsUI.h"
#include "../src/UI/battleUI.h"
#include "../src/UI/loadGameUI.h"
#include "../src/UI/inventoryUI.h"
#include "../src/UI/inputHandler.h"

#include "../src/Entities/player.h"
#include "../src/Entities/monster.h"

#include "../src/Utils/constants.h"
#include "../src/Utils/mathFunctions.h"
#include <windows.h>
#include <vector>
#include <iostream>

TEST_CASE("SelectionUI basic functionality") {
    COORD coord = {0, 0};
    SelectionUI ui(coord);

    std::vector<std::string> options = {"Option 1", "Option 2", "Option 3"};
    ui.SetOptions(options);
    //test initialization
    SUBCASE("Initial state") {
        CHECK(ui.GetSelectionIndex() == 0);
        CHECK(ui.GetOptions() == options);
        CHECK(ui.GetOption(0) == "Option 1");
    }
    //test moving down
    SUBCASE("Move selection down") {
        ui.MoveSelection(true);
        CHECK(ui.GetSelectionIndex() == 1);
        CHECK(ui.GetOption(1) == "Option 2");
    }
    //test moving up
    SUBCASE("Move selection up") {
        ui.MoveSelection(true);
        ui.MoveSelection(true);
        ui.MoveSelection(false);
        CHECK(ui.GetSelectionIndex() == 1);
        CHECK(ui.GetOption(1) == "Option 2");
    }
}
TEST_CASE("StartMenuUI basic functionality") {
    StartMenuUI startMenu;
    //test option setting
    SUBCASE("Initial state") {
        std::vector<std::string> options = {"New game", "Load game", "Highscores", "Exit"};
        CHECK(startMenu.GetOptions() == options);
        CHECK(startMenu.GetSelectionIndex() == 0);
    }
    //test moving up and down
    SUBCASE("Move selection") {
        startMenu.MoveSelection(true);
        CHECK(startMenu.GetSelectionIndex() == 1);

        startMenu.MoveSelection(true);
        startMenu.MoveSelection(true);
        startMenu.MoveSelection(true);
        CHECK(startMenu.GetSelectionIndex() == 3);

        startMenu.MoveSelection(false);
        CHECK(startMenu.GetSelectionIndex() == 2);
    }
}
TEST_CASE("StatsUI basic functionality") {
    Player player;
    player.SetStrength(10);
    player.SetMana(20);
    player.SetMaxHP(30);
    player.SetDexterity(40);
    player.SetStatPoints(5);

    StatsUI statsUI;

    //check option setting
    SUBCASE("Initial state") {
        std::vector<std::string> options = {"Strength", "Mana", "Health Points", "Dexterity"};
        CHECK(statsUI.GetOptions() == options);
        CHECK(statsUI.GetSelectionIndex() == 0);
    }
    //test getters
    SUBCASE("Check player stats") {
        CHECK(player.GetStrength() == 10);
        CHECK(player.GetMana() == 20);
        CHECK(player.GetMaxHP() == 30);
        CHECK(player.GetDexterity() == 40);
        CHECK(player.GetStatPoints() == 5);
    }
    //test moving up and down
    SUBCASE("Move selection") {
        
        statsUI.MoveSelection(true);
        CHECK(statsUI.GetSelectionIndex() == 1);

        statsUI.MoveSelection(true);
        statsUI.MoveSelection(true);
        CHECK(statsUI.GetSelectionIndex() == 3);

        statsUI.MoveSelection(false);
        CHECK(statsUI.GetSelectionIndex() == 2);
    }
}

TEST_CASE("InventoryUI: Initialization and rendering") {
    Player player;
    InventoryUI inventoryUI;


    // Mock some items and set them in the player's inventory
    Item sword("Sword", Item::ItemType::Weapon, 10);
    Item shield("Shield", Item::ItemType::Armor, 20);
    player.AddItem(sword);
    player.AddItem(shield);

    // Check initial selection index
    CHECK(inventoryUI.GetSelectionIndex() == 0);

    // Test rendering function (assume it works if no exceptions are thrown)
    CHECK_NOTHROW(inventoryUI.Render());

    // Move selection down and check the index
    inventoryUI.MoveSelection(true);
    CHECK(inventoryUI.GetSelectionIndex() == 1);

    // Move selection up and check the index
    inventoryUI.MoveSelection(false);
    CHECK(inventoryUI.GetSelectionIndex() == 0);
}

TEST_CASE("InputHandler: Initialization and user input") {
    InputHandler inputHandler;
    Player player;
    Map map;

    // We can't directly test UserInput due to its reliance on _kbhit() and _getch()
    // However, we can test the functions it calls
    CHECK_NOTHROW(inputHandler.UserInput(map, player));

    InventoryUI inventoryUI;
    StatsUI statsUI;

    // Test InventoryUserInput and StatsUserInput
    CHECK_NOTHROW(inputHandler.InventoryUserInput(inventoryUI));
    CHECK_NOTHROW(inputHandler.StatsUserInput(statsUI));
}

TEST_CASE("LoadGameUI: Initialization and options loading") {
    LoadGameUI loadGameUI("../Saves/");

    // Check that options are loaded correctly (this assumes there are files in the directory)
    CHECK(!loadGameUI.GetOptions().empty());

    // Check initial selection index
    CHECK(loadGameUI.GetSelectionIndex() == 0);

    // Move selection down and check the index
    loadGameUI.MoveSelection(true);
    CHECK(loadGameUI.GetSelectionIndex() == 1);

    // Move selection up and check the index
    loadGameUI.MoveSelection(false);
    CHECK(loadGameUI.GetSelectionIndex() == 0);
}

TEST_CASE("BattleUI: Initialization and rendering") {
    Player player;
    Monster monster;
    BattleUI battleUI(&monster);

    //Test getters
    CHECK(battleUI.getMonster() == &monster);

    // Test rendering functions (if no exception is thrown, its oki doki)
    CHECK_NOTHROW(battleUI.RenderGraphics());
    CHECK_NOTHROW(battleUI.Render());

    // Check initial selection index
    CHECK(battleUI.GetSelectionIndex() == 0);

    // Move selection down and check the index
    battleUI.MoveSelection(true);
    CHECK(battleUI.GetSelectionIndex() == 1);

    // Move selection up and check the index
    battleUI.MoveSelection(false);
    CHECK(battleUI.GetSelectionIndex() == 0);
}