#include <vector>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "MapGenerator/renderer.h"
#include "MapGenerator/map.h"
#include "Entities/player.h"
#include "UI/startMenuUI.h"
#include "UI/inventoryUI.h"
#include "UI/statsUI.h"
#include "UI/selectionUI.h"
#include "UI/inputHandler.h"
#include "constants.h"

bool isGameOver = false;

void Render(Map& map){
    if(!isGameOver){
        map.RenderStats();
        map.RenderPosition();
    }
}

void IntitialRender(Map& map){
    map.RenderAll();
}

void InitializeGame(){
    srand(time(0));
    system("cls");
    char buffer[50];
    std::cout << "Enter player name: ";
    std::cin.getline(buffer, 50);
    std::string name(buffer);

    system("cls");
    std::cout << "Pick a race:\n------------";
    SelectionUI raceSelectUI({0, 2});
    raceSelectUI.SetOptions({"Human", "Sorcerer", "Berserk"});
    raceSelectUI.Render();
    bool OpenRaceSelectUI = true;
    Player::PlayerRace race;
    while(OpenRaceSelectUI){
        InputHandler::RaceSelectInput(raceSelectUI, OpenRaceSelectUI, race);
    }
    Player p(race, name);

    Map map1(10, 10, 2, 2, &p);
    map1.GenerateMap();
    system("cls");
    IntitialRender(map1);
    while(!isGameOver){
        InputHandler::UserInput(map1, p, isGameOver);
    }
}

int main() {
    system("cls");
    StartMenuUI startUI;
    bool OpenStartUI = true;
    startUI.Render();
    while(OpenStartUI){
        InputHandler::StartUserInput(startUI, OpenStartUI, isGameOver);
    }
    if (!isGameOver) {
        InitializeGame();
    }

    return 0;
}