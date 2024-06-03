#if !TEST_IN_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#else
#define DOCTEST_CONFIG_DISABLE
#endif
#include "doctest.h"

#include "../src/MapGenerator/map.h"
#include "../src/MapGenerator/renderer.h"
#include "../src/Utils/constants.h"
#include "../src/Entities/player.h"
#include "../src/Utils/mathFunctions.h"

#include <windows.h>
#include <vector>
#include <iostream>

class MockPlayer : public Player {
public:
    unsigned GetGold() const { return 100; }
    unsigned GetLevel() const { return 10; }
    unsigned GetXP() const { return 200; }
    unsigned GetRequiredXP() const { return 300; }
    int GetHP() const { return 80; }
    unsigned GetMaxHP() const { return 100; }
};

TEST_SUITE("Test basic renders"){
    // Test case for ClearConsoleLines
    TEST_CASE("Test ClearConsoleLines") {
        Renderer renderer;
        CHECK_NOTHROW(renderer.ClearConsoleLines(0, 10));
    }

    // Test case for RenderTile
    TEST_CASE("Test RenderTile") {
        Renderer renderer;
        CHECK_NOTHROW(renderer.RenderTile(Constants::WALL));
        CHECK_NOTHROW(renderer.RenderTile(Constants::PATH));
        CHECK_NOTHROW(renderer.RenderTile(Constants::PLAYER));
        CHECK_NOTHROW(renderer.RenderTile(Constants::EXIT));
        CHECK_NOTHROW(renderer.RenderTile(Constants::TREASURE));
        CHECK_NOTHROW(renderer.RenderTile(Constants::MONSTER));
        CHECK_NOTHROW(renderer.RenderTile(' '));
    }
}

//=============================================================================
//All rendering functions use non-negative integers, which are hard set by
//the constructors of the Map class. Those value are pulled directly from
//the requirements for the project, so i won't be testing for negative values
//=============================================================================

TEST_SUITE("Test complex renders"){
    // Test case for RenderChunk
    TEST_CASE("Test RenderChunk") {
        Renderer renderer;
        std::vector<std::vector<char>> matrix = {
            {'#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '#'},
            {'#', '.', '@', '.', '#'},
            {'#', '.', '.', '.', '#'},
            {'#', '#', '#', '#', '#'}
        };

        CHECK_NOTHROW(renderer.RenderChunk(5, 5, matrix));
    }

    // Test case for RenderMap
    TEST_CASE("Test RenderMap") {
        Renderer renderer;
        std::vector<std::vector<char>> matrix = {
            {'#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '#'},
            {'#', '.', '@', '.', '#'},
            {'#', '.', '.', '.', '#'},
            {'#', '#', '#', '#', '#'}
        };

        CHECK_NOTHROW(renderer.RenderMap(5, 5, matrix));
    }

    // Test case for RenderPosition
    TEST_CASE("Test RenderPosition") {
        Renderer renderer;
        std::vector<std::vector<char>> matrix = {
            {'#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '#'},
            {'#', '.', '@', '.', '#'},
            {'#', '.', '.', '.', '#'},
            {'#', '#', '#', '#', '#'}
        };

        CHECK_NOTHROW(renderer.RenderPosition(5, 5, 2, 2, matrix));
    }

    // Test case for RenderAll
    TEST_CASE("Test RenderAll") {
        Renderer renderer;
        MockPlayer player;
        std::vector<std::vector<char>> matrix = {
            {'#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '#'},
            {'#', '.', '@', '.', '#'},
            {'#', '.', '.', '.', '#'},
            {'#', '#', '#', '#', '#'}
        };

        CHECK_NOTHROW(renderer.RenderAll(5, 5, matrix, &player));
    }

    // Test case for RenderStats
    TEST_CASE("Test RenderStats") {
        Renderer renderer;
        MockPlayer player;

        CHECK_NOTHROW(renderer.RenderStats(5, 5, &player));
    }
}

TEST_SUITE("Renderer getters and setters"){
    // Test setters and getters
    TEST_CASE("Test Setters and Getters") {
        Renderer renderer;
        renderer.SetChunkX(10);
        renderer.SetChunkY(20);

        CHECK(renderer.GetChunkX() == 10);
        CHECK(renderer.GetChunkY() == 20);
    }
}


//=============================================================================
// TEST_SUITE("Testing the map class"){
//     TEST_CASE("Map creation and initialization") {
//         Player player(Player::PlayerRace::Human, "Pesho");
//         Map map(10, 10, 2, 2, 1, &player);
//         map.GenerateMap();
//         SUBCASE("Map dimensions are initialized correctly") {
//             CHECK(map.GetWidth() == 10);
//             CHECK(map.GetHeight() == 10);
//         }

//         SUBCASE("Player position is initialized correctly") {
//             CHECK(map.GetPlayerX() == 0);
//             CHECK(map.GetPlayerY() == 0);
//         }

//         SUBCASE("Floor is initialized correctly") {
//             CHECK(map.GetFloor() == 1);
//         }
        
//         SUBCASE("Higher floor maps are generated correctly") {
//             for (int i = 0; i < 10; i++) {
//                 CHECK(map.GetWidth() == MathFunctions::Fib(Constants::STARTING_WIDTH[0], Constants::STARTING_WIDTH[1], map.GetFloor()-1));
//                 CHECK(map.GetHeight() == MathFunctions::Fib(Constants::STARTING_HEIGHT[0], Constants::STARTING_HEIGHT[1], map.GetFloor()-1));
//                 CHECK_NOTHROW(map = Map(MathFunctions::Fib(Constants::STARTING_WIDTH[0], Constants::STARTING_WIDTH[1], map.GetFloor()),
//                 MathFunctions::Fib(Constants::STARTING_HEIGHT[0], Constants::STARTING_HEIGHT[1], map.GetFloor()),
//                 MathFunctions::Fib(Constants::STARTING_MONSTERS[0], Constants::STARTING_MONSTERS[1], map.GetFloor()), 
//                 MathFunctions::Fib(Constants::STARTING_TREASURE[0], Constants::STARTING_TREASURE[1], map.GetFloor()), 
//                 map.GetFloor()+1, map.GetPlayer()));
//                 CHECK_NOTHROW(map.GenerateMap());
//             }
//         }
//     }
//     TEST_CASE("Map movement") {
//         Player* player = new Player(Player::PlayerRace::Human, "Pesho");
//         Map map(player);
//         map.GenerateMap();

//         SUBCASE("Move player within bounds") {
//             map.MovePlayer(1, 0); // Move player to the right
//             CHECK(map.GetPlayerX() == 1);
//             CHECK(map.GetPlayerY() == 0);
//         }

//         SUBCASE("Do not move player outside left bounds") {
//             map.MovePlayer(-1, 0); // Move player to the left
//             CHECK(map.GetPlayerX() == 0); // Player should not move outside the left boundary
//             CHECK(map.GetPlayerY() == 0);
//         }

//         SUBCASE("Do not move player outide top bounds") {
//             // Assuming there's a wall at (0, 1) after initialization
//             map.MovePlayer(0, -1); // Try to move player up
//             CHECK(map.GetPlayerX() == 0); // Player should not move into the wall
//             CHECK(map.GetPlayerY() == 0);
//         }
//         delete player;
//     }
// }
