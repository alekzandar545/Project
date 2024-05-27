#include "map.h"
#include "../constants.h"
#include "renderer.h"
#include "conio.h"
#include "windows.h"
#include <iostream>

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

void Renderer::RenderChunk(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix) const{ //should drop the parameter probably
    ClearConsoleLines(1, 1 + CHUNK_SIZE[1] + 1); // deletes map without the stats //+1 for top render and +1 for bottom render
    unsigned chunkX = CHUNK_COORDS[0];
    unsigned chunkY = CHUNK_COORDS[1];
    unsigned chunkHeight = CHUNK_SIZE[1];
    if(height - chunkY != 0)
        chunkHeight = Min(height - chunkY, chunkHeight);
    unsigned chunkWidth = CHUNK_SIZE[0];
    if(width - chunkX != 0)
        chunkWidth = Min(width - chunkX, chunkWidth);

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
            if(matrix[chunkY-1][i] == WALL)
                std::cout << BORDER_TOP;
            else
                RenderTile(matrix[chunkY-1][i]);
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
        else if(matrix[i][chunkX-1] == WALL)
            std::cout << BORDER_SIDE;
        else{
            RenderTile(matrix[i][chunkX-1]);
        }
        //middle part
        for (size_t j = chunkX; j < chunkX + chunkWidth; j++)
        {
            RenderTile(matrix[i][j]);
        }
        //right border
        if(chunkX + chunkWidth == width)
            std::cout << BORDER_SIDE;
        else if(matrix[i][chunkX + chunkWidth] == WALL)
            std::cout << BORDER_SIDE;
        else{
            RenderTile(matrix[i][chunkX + chunkWidth]);
        } 
        std::cout << '\n';   
    }
    //bottom
    std::cout << BORDER_SIDE;
    if((chunkY + chunkHeight) == height){
        for (size_t i = 0; i < chunkWidth; i++)
        {
            std::cout << BORDER_BOTTOM;
        }
    }
    else{
        for (size_t i = chunkX; i < chunkX + chunkWidth; i++)
        {
            if(matrix[chunkY + chunkHeight][i] == WALL)
                std::cout << BORDER_BOTTOM;
            else
                RenderTile(matrix[chunkY + chunkHeight][i]);
        }    
    }
    std::cout << BORDER_SIDE; 
    std::cout << '\n';
}

void Renderer::RenderMap(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix) const{//renders the entire map //overflows when map gets bigger
    //clear the console
    system("cls");
    //print top border
    SetConsoleTextAttribute(CURR_HANDLE, 8);
    for (size_t i = 0; i < width + 2; i++)
        std::cout << BORDER_TOP;
    std::cout << '\n';     
    //print map
    for (size_t i = 0; i < height; ++i)
    {   
        std::cout << BORDER_SIDE;
        for (size_t j = 0; j < width; ++j)
        {   
            RenderTile(matrix[i][j]);
        }
        std::cout << BORDER_SIDE << '\n';
    }
    //print bottom border
    for (size_t i = 0; i < matrix[0].size() + 2; i++)
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
void Renderer::RenderPosition(const unsigned height, const unsigned width, const unsigned playerX, const unsigned playerY, const std::vector<std::vector<char>> matrix){
    
    //loading new chunks
    if(playerX < CHUNK_COORDS[0]){
        CHUNK_COORDS[0] -= CHUNK_SIZE[0];
        RenderChunk(height, width, matrix);
    }
    else if(playerX > CHUNK_COORDS[0]+CHUNK_SIZE[0]-1){
        CHUNK_COORDS[0] += CHUNK_SIZE[0];
        RenderChunk(height, width, matrix); 
    }
    else if(playerY < CHUNK_COORDS[1]){
        CHUNK_COORDS[1] -= CHUNK_SIZE[1];
        RenderChunk(height, width, matrix);
    }
    else if(playerY > CHUNK_COORDS[1]+CHUNK_SIZE[1]-1){
        CHUNK_COORDS[1] += CHUNK_SIZE[1];
        RenderChunk(height, width, matrix); 
    }
    short offsetX = 1 - CHUNK_COORDS[0]; //wall
    short offsetY = 2 - CHUNK_COORDS[1]; // wall and stats
    //should adjust for chnk offset //also shouldnt render at the ends of chunks
    //move validation to setters
    SetConsoleCursorPosition(CURR_HANDLE, {(short)(playerX+offsetX), (short)(playerY+offsetY)});//center
    RenderTile(matrix[playerY][playerX]);
    if(playerX > 0 && playerX != CHUNK_COORDS[0]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(playerX+offsetX-1), (short)(playerY+offsetY)});//left
        RenderTile(matrix[playerY][playerX-1]);
    }
    if(playerX+1 < width && playerX+1 != CHUNK_COORDS[0] + CHUNK_SIZE[0]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(playerX+offsetX+1), (short)(playerY+offsetY)});//right
        RenderTile(matrix[playerY][playerX+1]);
    }
    if(playerY > 0 && playerY != CHUNK_COORDS[1]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(playerX+offsetX), (short)(playerY+offsetY-1)});//down
        RenderTile(matrix[playerY-1][playerX]);
    }
    if(playerY+1 < height && playerY+1 != CHUNK_COORDS[1] + CHUNK_SIZE[1]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(playerX+offsetX), (short)(playerY+offsetY+1)});//up
        RenderTile(matrix[playerY+1][playerX]);
    }
    SetConsoleCursorPosition(CURR_HANDLE, {0,0});
}

void Renderer::RenderAll(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix, Player* player) const{
    //now time to print the offset vertically;
    RenderStats(height, width, player);
    RenderChunk(height, width, matrix);
    //controls info
    std::cout << "I - inventory" << '\n' << "E - select" << '\n' << "G - stats";
}

void Renderer::RenderStats(const unsigned height, const unsigned width, Player* player) const{
    SetConsoleCursorPosition(CURR_HANDLE, {0,0});
    SetConsoleTextAttribute(CURR_HANDLE, 6);
    std::cout << "Gold: " << player->gold << "   ";
    SetConsoleTextAttribute(CURR_HANDLE, 2);
    std::cout << "Level: " << player->level << "    ";
    std::cout << "XP: " << player->xp << '/' << player->requiredXp << "   ";
    SetConsoleTextAttribute(CURR_HANDLE, 12);
    std::cout << "HP: " << player->HP << '/' << player->maxHP << padding << '\n';
    SetConsoleTextAttribute(CURR_HANDLE, 8);
    //SetConsoleCursorPosition(CURR_HANDLE, {(short)width,(short)(height+1)});
}

//setters
void Renderer::SetChunkX(const unsigned x){
    CHUNK_COORDS[0] = x;
}
void Renderer::SetChunkY(const unsigned y){
    CHUNK_COORDS[1] = y;
}
