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
#include "Utils/constants.h"
#include "Utils/gameLoader.h"
#include "Utils/gameInitializer.h"



int main() {
    Constants::isGameOver = false;
    srand(time(0));
    system("cls");
    StartMenuUI startUI;
    bool OpenStartUI = true;
    bool newGame = false;
    std::string loadDir;
    startUI.Render();
    while(OpenStartUI){
        InputHandler::StartUserInput(startUI, OpenStartUI, newGame, loadDir);
    }
    if(newGame && !Constants::isGameOver)
        GameInitializer::NewGame();
    else if(!Constants::isGameOver)
        GameInitializer::LoadGame(loadDir);
    return 0;
}