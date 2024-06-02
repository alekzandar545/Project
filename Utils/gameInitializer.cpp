#include "gameInitializer.h"
#include "../UI/selectionUI.h"
#include "../UI/inputHandler.h"
#include "gameState.h"
#include "gameLoader.h"
#include <iostream>
#include <windows.h>

Player GameInitializer::CreatePlayer() {
    char buffer[50];
    std::cout << "Enter player name: ";
    std::cin.getline(buffer, 50);
    std::string name(buffer);

    system("cls");
    std::cout << "Pick a race:\n------------";
    SelectionUI raceSelectUI({0, 2});
    raceSelectUI.SetOptions({"Human", "Berserk", "Sorcerer"});
    raceSelectUI.Render();
    bool OpenRaceSelectUI = true;
    Player::PlayerRace race;
    while (OpenRaceSelectUI) {
        InputHandler::RaceSelectUserInput(raceSelectUI, OpenRaceSelectUI, race);
    }
    system("cls");
    return Player(race, name);
}

Map GameInitializer::CreateMap(Player* player) {
    Map map1(10, 10, 2, 2, 1, player);
    map1.GenerateMap();
    return map1;
}

void GameInitializer::NewGame() {
    system("cls");
    Player player = CreatePlayer();
    Map map = CreateMap(&player);
    GameState::SetGameMap(&map);
    GameState::SetGamePlayer(&player);
    map.RenderAll(); // first render

    while (!GameState::isGameOver) {
        InputHandler::UserInput(map, player);
    }
}

void GameInitializer::LoadGame(const std::string& saveDir) {
    system("cls");
    Player player;
    Map map;
    GameLoader::LoadGame(player, map, saveDir);
    GameState::SetGameMap(&map);
    GameState::SetGamePlayer(&player);
    map.RenderAll(); // first render

    while (!GameState::isGameOver) {
        InputHandler::UserInput(map, player);
    }
}