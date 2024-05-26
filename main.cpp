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

//enum Directions { STOP = 0, LEFT, RIGHT, UP, DOWN }; //gotta use those i think>>?
bool isGameOver = false; 



//render stats and level etc later on
void Render(Map& map){
    map.RenderStats();
    map.RenderPosition();
}
void IntitialRender(Map& map){
    map.RenderAll();
}

void UserInput(Map& map, Player& p) 
{ 
    // Checks if a key is pressed or not 
    if (_kbhit()) { 
        // Getting the pressed key 
        switch (_getch()) { 
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
            InventoryUI ui({0,0}, p);
            ui.Render();
            break;
        }
        case 'x': 
            isGameOver = true; 
            break; 
        } 
    } 
} 

int main()
{   
    //steps:
    //1)startUI -> need load screen
    //2)PlayerCreation
    //3)Visualize map
    system("cls");
    srand(time(0));
    Player p(Player::PlayerRace::Berserk, "Pesho");
	Map map1(10,10,2,2,&p);
    map1.GenerateMap();
    IntitialRender(map1);
    while(!isGameOver){
        UserInput(map1, p);
    }
    return 0;
}