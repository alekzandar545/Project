#include "vector"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "MapGenerator/renderer.h"
#include "MapGenerator/map.h"
#include "Entities/player.h"

//enum Directions { STOP = 0, LEFT, RIGHT, UP, DOWN }; //gotta use those i think>>?
bool isGameOver = false; 
HANDLE mainHandle = GetStdHandle(STD_OUTPUT_HANDLE);



//render stats and level etc later on
void Render(Map& map, Player& p){
    SetConsoleCursorPosition(mainHandle, {0,0});
    std::cout << "Gold: " << p.gold << "   " << "XP: " << p.xp << '/' << p.requiredXp << '\n';
    Renderer* renderer = Renderer::GetInstance(&map); 
    renderer->RenderPosition();
    //std::cout << map.GetPlayerX() << map.GetPlayerY();
}

void UserInput(Map& map, Player& p) 
{ 
    // Checks if a key is pressed or not 
    if (_kbhit()) { 
        // Getting the pressed key 
        switch (_getch()) { 
        case 'a': 
            map.MovePlayer(-1, 0);
            Render(map, p);
            break; 
        case 'd': 
            map.MovePlayer(1, 0);
            Render(map, p);
            break; 
        case 'w': 
            map.MovePlayer(0, -1);
            Render(map, p);
            break; 
        case 's': 
            map.MovePlayer(0, 1);
            Render(map, p);
            break; 
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
    Player p(Player::PlayerRace::Berserk);
	Map map1(10,10,2,2,&p);
    map1.GenerateMap();
    Render(map1, p);
    while(!isGameOver){
        UserInput(map1, p);
    }
    return 0;
}