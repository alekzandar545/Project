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
#include "constants.h"

bool isGameOver = false;

// Render stats and level, etc. later on
void Render(Map& map){
    if(!isGameOver){
        map.RenderStats();
        map.RenderPosition();
    }
}

void IntitialRender(Map& map){
    map.RenderAll();
}

bool InventoryUserInput(InventoryUI& ui) 
{ 
    if (_kbhit()) { 
        int ch = _getch(); 
        switch (ch) { 
            case 'w': // up arrow
                ui.MoveSelection(0);
                break; 
            case 's': // down arrow
                ui.MoveSelection(1);
                break; 
            case 'e':
                ui.GetPlayer()->EquipItem(ui.GetSelectionIndex());
                ui.Render();
                break;
            case 'x':
                ui.GetPlayer()->SellItem(ui.GetSelectionIndex());
                system("cls");//need to rerender everything
                ui.CheckSold();
                ui.Render();
                break;
            case 'i':
                return false;
        } 
    } 
    return true;
}

bool StatsUserInput(StatsUI& ui) 
{ 
    if (_kbhit()) { 
        int ch = _getch(); 
        switch (ch) { 
            case 'w': // up arrow
                ui.MoveSelection(0);
                break; 
            case 's': // down arrow
                ui.MoveSelection(1);
                break; 
            case 'e':
                if(ui.GetOption(ui.GetSelectionIndex()) == "Strength")
                    ui.GetPlayer()->AddStrength();
                else if(ui.GetOption(ui.GetSelectionIndex()) == "Mana")
                    ui.GetPlayer()->AddMana();
                else if(ui.GetOption(ui.GetSelectionIndex()) == "Health Points")
                    ui.GetPlayer()->AddHP();
                else if(ui.GetOption(ui.GetSelectionIndex()) == "Dexterity")
                    ui.GetPlayer()->AddDexterity();
                ui.Render();
                break;
            case 'g':
                return false;
        } 
    } 
    return true;
}

void UserInput(Map& map, Player& p) 
{ 
    if (_kbhit()) { 
        int ch = _getch(); 
        switch (ch) { 
            case 'a': 
                map.MovePlayer(-1, 0);
                Render(map);
                break; 
            case 'd': 
                map.MovePlayer(1, 0);
                Render(map);
                break; 
            case 'w': 
                map.MovePlayer(0, -1);
                Render(map);
                break; 
            case 's': 
                map.MovePlayer(0, 1);
                Render(map);
                break; 
            case 'i':{
                system("cls");
                InventoryUI ui(&p);
                bool isOpen = true;
                ui.Render();
                while(isOpen){
                    isOpen = InventoryUserInput(ui);
                }
                system("cls");
                map.RenderAll();
                break;
            }
            case 'g':{
                system("cls");
                StatsUI ui(&p);
                bool isOpen = true;
                ui.Render();
                while(isOpen){
                    isOpen = StatsUserInput(ui);
                }
                system("cls");
                map.RenderAll();
                break;
            }
            case 'x': 
                isGameOver = true; 
                system("cls");
                break; 
        } 
    } 
}

void StartUserInput(StartMenuUI& ui, bool& OpenStartUI) 
{ 
    if (_kbhit()) { 
        int ch = _getch(); 
        switch (ch) { 
            case 'w': // up arrow
                ui.MoveSelection(0);
                break; 
            case 's': // down arrow
                ui.MoveSelection(1);
                break; 
            case 'e':
                switch(ui.GetSelectionIndex()){ 
                    case 0: // new game
                        OpenStartUI = false;
                        break; 
                    case 1: // load game
                        // load game interface
                        break; 
                    case 2: // highscores
                        // highscores interface
                        break; 
                    case 3: // exit
                        isGameOver = true;
                        OpenStartUI = false;
                        system("cls");
                        break;
                }
                break;
        } 
    } 
}

void RaceSelectInput(SelectionUI& ui, bool& OpenRaceSelectUI, Player::PlayerRace& race) 
{ 
    if (_kbhit()) { 
        int ch = _getch(); 
        switch (ch) { 
            case 'w': // up arrow
                ui.MoveSelection(0);
                break; 
            case 's': // down arrow
                ui.MoveSelection(1);
                break; 
            case 'e':
                switch(ui.GetSelectionIndex()){ 
                    case 0: //Human
                        race = Player::PlayerRace::Human;
                        break; 
                    case 1: //Sorcerer
                        race = Player::PlayerRace::Sorcerer;
                        break; 
                    case 2: //Berserk
                        race = Player::PlayerRace::Berserk;
                        break; 
                    default:
                        race = Player::PlayerRace::Human;
                        break;

                }
                OpenRaceSelectUI = false;
                system("cls");
                break;
        } 
    } 
}

void InitializeGame(){
    srand(time(0));
    //name
    system("cls");
    char buffer[50];
    std::cout << "Enter player name: ";
    std::cin.getline(buffer, 50);
    std::string name(buffer);
    //race
    system("cls");
    std::cout << "Pick a race:\n------------";
    SelectionUI raceSelectUI({0,2});
    raceSelectUI.SetOptions({"Human","Sorcerer","Berserk"});
    raceSelectUI.Render();
    bool OpenRaceSelectUI = true;
    Player::PlayerRace race;
    while(OpenRaceSelectUI){
        RaceSelectInput(raceSelectUI, OpenRaceSelectUI, race);
    }
    Player p(race, name);
    //map creation
    Map map1(10,10,2,2,&p);
    map1.GenerateMap();
    system("cls");
    IntitialRender(map1);
    while(!isGameOver){
        UserInput(map1, p);
    }
}

int main()
{   
    system("cls");
    StartMenuUI startUI;
    bool OpenStartUI = true;
    startUI.Render();
    while(OpenStartUI){
        StartUserInput(startUI, OpenStartUI);
    }
    if (!isGameOver) {
        InitializeGame();
    }

    return 0;
}
