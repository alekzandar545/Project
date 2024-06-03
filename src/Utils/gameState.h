#pragma once
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include "../MapGenerator/map.h"
#include "../Entities/player.h"
#include "gameSaver.h"

/**
 * @class GameState
 * @brief Represents the state of the game.
 * 
 * The GameState class provides static methods and variables to manage the state of the game.
 * It allows setting and getting the game map and player, as well as controlling the game state.
 */
class GameState {
public:
    // Constructors
    GameState() = default;
    ~GameState();

    // Game State
    static std::atomic<bool> isGameOver; /**< Indicates whether the game is over. */
    static std::atomic<bool> isSleeping; /**< Indicates whether the game is in sleep mode. */

    static void EndGame(); /**< Ends the game. */
    static void sleepAndIgnoreInputs(int seconds); /**< Puts the game to sleep for the specified number of seconds, ignoring inputs. */

    // Setters
    static void SetGameMap(Map* map); /**< Sets the game map. */
    static void SetGamePlayer(Player* player); /**< Sets the game player. */

    // Getters
    static Map* GetGameMap(); /**< Gets the game map. */
    static Player* GetGamePlayer(); /**< Gets the game player. */

private:
    static std::mutex stateMutex; /**< Mutex for thread-safe access to the game state. */
    static Map* map; /**< Pointer to the game map. */
    static Player* player; /**< Pointer to the game player. */
};
