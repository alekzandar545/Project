#include "gameState.h"

std::atomic<bool> GameState::isGameOver{false};
std::atomic<bool> GameState::isSleeping{false};
Map* GameState::map = nullptr;
Player* GameState::player = nullptr;
std::mutex GameState::stateMutex;

//constructors
GameState::~GameState(){
    delete player;
    delete map;
}

void GameState::EndGame() {
    std::lock_guard<std::mutex> lock(stateMutex);
    if (map && player) {
        GameSaver::SaveHighscore(*player,"../Highscores/");
    }
    isGameOver = true;
}
void GameState::sleepAndIgnoreInputs(int seconds) {
    isSleeping = true;
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    isSleeping = false;
}

//setters
void GameState::SetGameMap(Map* newMap) {
    std::lock_guard<std::mutex> lock(stateMutex);
    map = newMap;
}

void GameState::SetGamePlayer(Player* newPlayer) {
    std::lock_guard<std::mutex> lock(stateMutex);
    player = newPlayer;
}
//getters
Map* GameState::GetGameMap(){
    std::lock_guard<std::mutex> lock(stateMutex);
    return map;
}
Player* GameState::GetGamePlayer(){
    std::lock_guard<std::mutex> lock(stateMutex);
    return player;
}