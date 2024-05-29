#pragma once

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
#include "gameLoader.h"

class GameInitializer{
public:
    static Player CreatePlayer(){
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
        while(OpenRaceSelectUI){
            InputHandler::RaceSelectUserInput(raceSelectUI, OpenRaceSelectUI, race);
        }
        system("cls");
        return Player(race, name);
    }

    static Map CreateMap(Player* player) {
        Map map1(10, 10, 2, 2, player);
        map1.GenerateMap();
        return map1;
    }

    static void NewGame(){
        system("cls");
        Player player = CreatePlayer();
        Map map = CreateMap(&player);
        map.RenderAll(); //first render

        bool isGameOver = false;
        while(!isGameOver){
            InputHandler::UserInput(map, player, isGameOver);
        }
    }

    static void LoadGame(std::string saveDir){
        system("cls");
        Player player;
        Map map;
        GameLoader::LoadGame(player,map,saveDir);
        map.RenderAll(); //first render

        bool isGameOver = false;
        while(!isGameOver){
            InputHandler::UserInput(map, player, isGameOver);
        }
    }
private:
};