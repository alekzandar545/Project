#include "map.h"
#include "constants.h"
#include "renderer.h"
#include "conio.h"
#include "windows.h"
#include <iostream>

static unsigned CHUNK_COORDS[] = {0,0};//should integrate this in class
HANDLE CURR_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE); 

//auxiliary functions
unsigned Min(const unsigned a, const unsigned b){
    if(a < b)
        return a;
    else
        return b;
}

void ClearConsoleLines(int startLine, int endLine) {
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD coord;
    DWORD written;
    // Get the current screen buffer info
    if (!GetConsoleScreenBufferInfo(CURR_HANDLE, &csbi)) {
        return;
    }
    // Calculate the width of the console
    int consoleWidth = csbi.dwSize.X;
    for (int line = startLine; line <= endLine; ++line) {
        coord.X = 0;
        coord.Y = line;
        FillConsoleOutputCharacter(CURR_HANDLE, ' ', consoleWidth, coord, &written);
        FillConsoleOutputAttribute(CURR_HANDLE, csbi.wAttributes, consoleWidth, coord, &written);
    }
}

//singleton pattern
Renderer* Renderer::instancePtr = nullptr;
Map* Renderer::map;
unsigned Renderer::floor = 0;

Renderer* Renderer::GetInstance(Map* map)
{
    if(!instancePtr){
        SetConsoleTextAttribute(CURR_HANDLE, 8);
        instancePtr = new Renderer();
        Renderer::map = map;
        instancePtr->RenderChunk(CHUNK_COORDS);
    }
    return instancePtr;
}

//Rendering
void Renderer::RenderTile(char c) const{
    switch(c){
    case WALL:
        SetConsoleTextAttribute(CURR_HANDLE, 8);
        break;
    case PATH:
        SetConsoleTextAttribute(CURR_HANDLE, 8); 
        break;
    case PLAYER:
        SetConsoleTextAttribute(CURR_HANDLE, 3);
        break;
    case EXIT:
        SetConsoleTextAttribute(CURR_HANDLE, 10);
        break;
    case TREASURE:
        SetConsoleTextAttribute(CURR_HANDLE, 6);
        break; 
    case MONSTER:
        SetConsoleTextAttribute(CURR_HANDLE, 12);
        break;                                  
    default:
        SetConsoleTextAttribute(CURR_HANDLE, 15);
        break;
    }
    std::cout << c;
    SetConsoleTextAttribute(CURR_HANDLE, 8);
}

void Renderer::RenderChunk(const unsigned* ChunkCoords) const{ //should drop the parameter probably
    ClearConsoleLines(1,12); // deletes map without the stats
    unsigned chunkX = ChunkCoords[0];
    unsigned chunkY = ChunkCoords[1];
    unsigned chunkHeight = CHUNK_SIZE[1];
    if(map->height - chunkY != 0)
        chunkHeight = Min(map->height - chunkY, chunkHeight);
    unsigned chunkWidth = CHUNK_SIZE[0];
    if(map->width - chunkX != 0)
        chunkWidth = Min(map->width - chunkX, chunkWidth);

    //top part
    std::cout << BORDER_SIDE;
    if(chunkY == 0){
        for (size_t i = 0; i < chunkWidth; i++)
        {
            std::cout << BORDER_TOP;
        }
    }
    else{
        for (size_t i = chunkX; i < chunkX + chunkWidth; i++)
        {
            if(map->matrix[chunkY-1][i] == WALL)
                std::cout << BORDER_TOP;
            else
                RenderTile(map->matrix[chunkY-1][i]);
        }            
    }
    std::cout << BORDER_SIDE;
    std::cout << '\n';  
    //middle part
    for (size_t i = chunkY; i < chunkY + chunkHeight; i++)
    {
        //left border
        if(chunkX == 0)
            std::cout << BORDER_SIDE;
        else if(map->matrix[i][chunkX-1] == WALL)
            std::cout << BORDER_SIDE;
        else{
            RenderTile(map->matrix[i][chunkX-1]);
        }
        //middle part
        for (size_t j = chunkX; j < chunkX + chunkWidth; j++)
        {
            RenderTile(map->matrix[i][j]);
        }
        //right border
        if(chunkX + chunkWidth == map->width)
            std::cout << BORDER_SIDE;
        else if(map->matrix[i][chunkX + chunkWidth] == WALL)
            std::cout << BORDER_SIDE;
        else{
            RenderTile(map->matrix[i][chunkX + chunkWidth]);
        } 
        std::cout << '\n';   
    }
    //bottom
    std::cout << BORDER_SIDE;
    if((chunkY + chunkHeight) == map->height){
        for (size_t i = 0; i < chunkWidth; i++)
        {
            std::cout << BORDER_BOTTOM;
        }
    }
    else{
        for (size_t i = chunkX; i < chunkX + chunkWidth; i++)
        {
            if(map->matrix[chunkY + chunkHeight][i] == WALL)
                std::cout << BORDER_BOTTOM;
            else
                RenderTile(map->matrix[chunkY + chunkHeight][i]);
        }    
    }
    std::cout << BORDER_SIDE; 
    std::cout << '\n';
}

void Renderer::RenderMap() const{//renders the entire map //overflows when map gets bigger
    //clear the console
    system("cls");
    //print top border
    SetConsoleTextAttribute(CURR_HANDLE, 8);
    for (size_t i = 0; i < map->width + 2; i++)
        std::cout << BORDER_TOP;
    std::cout << '\n';     
    //print map
    for (size_t i = 0; i < map->height; ++i)
    {   
        std::cout << BORDER_SIDE;
        for (size_t j = 0; j < map->width; ++j)
        {   
            RenderTile(map->matrix[i][j]);
        }
        std::cout << BORDER_SIDE << '\n';
    }
    //print bottom border
    for (size_t i = 0; i < map->matrix[0].size() + 2; i++)
        std::cout << BORDER_BOTTOM;
    std::cout << '\n';
}
//////////!DANGER ZONE!///////////
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}
void Renderer::RenderPosition() const{
    //loading new floor
    if(floor != map->floor){ //this condition is invalid
        floor++;
        CHUNK_COORDS[0] = 0;
        CHUNK_COORDS[1] = 0;
        RenderChunk(CHUNK_COORDS);
    }

    //loading new chunks
    if(map->playerX < CHUNK_COORDS[0]){
        CHUNK_COORDS[0] -= CHUNK_SIZE[0];
        RenderChunk(CHUNK_COORDS);
    }
    else if(map->playerX > CHUNK_COORDS[0]+CHUNK_SIZE[0]-1){
        CHUNK_COORDS[0] += CHUNK_SIZE[0];
        RenderChunk(CHUNK_COORDS); 
    }
    else if(map->playerY < CHUNK_COORDS[1]){
        CHUNK_COORDS[1] -= CHUNK_SIZE[1];
        RenderChunk(CHUNK_COORDS);
    }
    else if(map->playerY > CHUNK_COORDS[1]+CHUNK_SIZE[1]-1){
        CHUNK_COORDS[1] += CHUNK_SIZE[1];
        RenderChunk(CHUNK_COORDS); 
    }
    short offsetX = 1 - CHUNK_COORDS[0]; //wall
    short offsetY = 2 - CHUNK_COORDS[1]; // wall and stats
    //should adjust for chnk offset //also shouldnt render at the ends of chunks
    //move validation to setters
    SetConsoleCursorPosition(CURR_HANDLE, {(short)(map->playerX+offsetX), (short)(map->playerY+offsetY)});//center
    RenderTile(map->matrix[map->playerY][map->playerX]);
    if(map->playerX > 0 && map->playerX != CHUNK_COORDS[0]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(map->playerX+offsetX-1), (short)(map->playerY+offsetY)});//left
        RenderTile(map->matrix[map->playerY][map->playerX-1]);
    }
    if(map->playerX+1 < map->width && map->playerX+1 != CHUNK_COORDS[0] + CHUNK_SIZE[0]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(map->playerX+offsetX+1), (short)(map->playerY+offsetY)});//right
        RenderTile(map->matrix[map->playerY][map->playerX+1]);
    }
    if(map->playerY > 0 && map->playerY != CHUNK_COORDS[1]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(map->playerX+offsetX), (short)(map->playerY+offsetY-1)});//down
        RenderTile(map->matrix[map->playerY-1][map->playerX]);
    }
    if(map->playerY+1 < map->height && map->playerY+1 != CHUNK_COORDS[1] + CHUNK_SIZE[1]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(map->playerX+offsetX), (short)(map->playerY+offsetY+1)});//up
        RenderTile(map->matrix[map->playerY+1][map->playerX]);
    }
    SetConsoleCursorPosition(CURR_HANDLE, {0,0});
}
