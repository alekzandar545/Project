#include "vector"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "map.h"

//enum Directions { STOP = 0, LEFT, RIGHT, UP, DOWN }; //gotta use those i think>>?
//bool isGameOver = false;
bool isGameOver = false; 

//render stats and level etc later on
void Render(Map& map){
    //map.RenderMap();
    map.RenderPosition();

}

void UserInput(Map& map) 
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
        case 'x': 
            isGameOver = true; 
            break; 
        } 

    } 
} 
int main()
{
    srand(time(0));
	Map map1(10,10,2,2);
    map1.GenerateMap();
    map1.RenderMap();
    while(!isGameOver){
        UserInput(map1);
    }
    
    return 0;
}