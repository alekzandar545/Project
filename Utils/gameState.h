#pragma once
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include "../MapGenerator/map.h"
#include "../Entities/player.h"
#include "gameSaver.h"

class GameState {
public:
    // Constructors
    GameState() = default;
    ~GameState();

    // Game State
    static std::atomic<bool> isGameOver;
    static std::atomic<bool> isSleeping;

    static void EndGame();
    static void sleepAndIgnoreInputs(int seconds);

    // Setters
    static void SetGameMap(Map* map);
    static void SetGamePlayer(Player* player);

private:
    static std::mutex stateMutex;
    static Map* map;
    static Player* player;
};
