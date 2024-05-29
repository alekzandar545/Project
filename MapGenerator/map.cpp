#include <vector>
#include <iostream>
#include <cmath>
#include <windows.h>
#include "map.h"
#include "../constants.h"
#include "../Entities/player.h"
#include "../Entities/monster.h"
#include "../Events/eventHandler.h"
#include "../UI/inputHandler.h"

//auxiliary functions //outta class in cpp file
void Swap(unsigned& a, unsigned& b){
    unsigned c = a;
    a = b;
    b = c;
}
void Shuffle(std::vector<unsigned>& a){
    for (int i = 0; i < a.size(); ++i)
    {
        Swap(a[i], a[rand() % a.size()]);
    }
}

//big4
Map::Map(Player* player)
    : player(player), floor(0), playerX(0), playerY(0), height(0), width(0) {
}

Map::Map(const unsigned width, const unsigned height, const unsigned monsterCount, const unsigned treasureCount, Player* player)
    : width(width), height(height), monsterCount(monsterCount), treasureCount(treasureCount), player(player), floor(0), playerX(0), playerY(0) {
}

Map::Map(const unsigned width, const unsigned height, const unsigned playerX, const unsigned playerY, const unsigned monsterCount,
        const unsigned treasureCount, const unsigned floor, std::vector<std::vector<char>> matrix, Player* player)
        : width(width), height(height), playerX(playerX), playerY(playerY), monsterCount(monsterCount), treasureCount(treasureCount), floor(floor), matrix(matrix), player(player) {}

Map::Map(const Map& other)
    : matrix(other.matrix), height(other.height), width(other.width), monsterCount(other.monsterCount), treasureCount(other.treasureCount), playerX(other.playerX), playerY(other.playerY), floor(other.floor), player(other.player) {
}

Map& Map::operator=(const Map& other) {
    if (&other == this)
        return *this;

    matrix = other.matrix;
    height = other.height;
    width = other.width;
    monsterCount = other.monsterCount;
    treasureCount = other.treasureCount;
    playerX = other.playerX;
    playerY = other.playerY;
    //floor = other.floor;
    player = other.player;
    return *this;
}

Map::~Map() = default;

//Creation
void Map::Initialize(){
    for (int i = 0; i < matrix.size(); ++i)
        for (int j = 0; j < matrix[0].size(); ++j)
            matrix[i][j] = Constants::WALL;
    CreatePath(0, 0);
}
void Map::CreatePath(const int i, const int j){ //Use DFS 
    int directions[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
    std::vector<unsigned> visitOrder = {0,1,2,3};
    //out of boundary
    if(i < 0 || j < 0 || i >= height || j >= width) return ;
    //visited, go back to the coming direction, return 
    if(matrix[i][j] == Constants::PATH) return ;

    //some neightbors are visited in addition to the coming direction, return
    //this is to avoid circles in maze
    if(countVisitedNeighbor(i, j) > rand() % LABYRYINTH +  1) return ;

    matrix[i][j] = Constants::PATH; // visited

    //shuffle the visitOrder
    Shuffle(visitOrder);
    
    for (int k = 0; k < 4; ++k)
    {
        int ni = i + directions[visitOrder[k]][0];
        int nj = j + directions[visitOrder[k]][1];
        CreatePath(ni, nj);
    }
}
int Map::countVisitedNeighbor(const int i, const int j) const{
    int directions[][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int count = 0;
    for (int k = 0; k < 4; ++k)
    {
        int ni = i + directions[k][0];
        int nj = j + directions[k][1];
        //out of boundary
        if(ni < 0 || nj < 0 || ni >= height || nj >= width) continue;
        if(matrix[ni][nj] == Constants::PATH) count++;//visited
    }
    return count;
}
void Map::GenerateMap(){
    matrix.clear();
    std::vector<char> row(width);
    for (int i = 0; i < height; ++i)
    {
        matrix.push_back(row);
    }
    Initialize();
    CreatePlayer();
    CreateExit();
    CreateTreasure();
    CreateMonsters();
}

void Map::CreateTreasure(){
    //store possible indexes in vector and then pick 6 random(after each pick, remove one)
    std::vector<unsigned> validIndexes;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if(matrix[i][j] != Constants::WALL && matrix[i][j] != Constants::TREASURE && matrix[i][j] != Constants::MONSTER &&
               matrix[i][j] != Constants::PLAYER && matrix[i][j] != Constants::EXIT){
                validIndexes.push_back(i*width + j);//adding ones so no multiplication by 0
            }
        }
    }
    Shuffle(validIndexes); //what if treasure is more than free tiles?  
    for (size_t i = 0; i < treasureCount; i++)
    {
        matrix[validIndexes[i]/width][validIndexes[i]%width] = Constants::TREASURE;
    }
}
void Map::CreateMonsters(){
    //store possible indexes in vector and then pick 6 random(after each pick, remove one)
    std::vector<unsigned> validIndexes;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if(matrix[i][j] != Constants::WALL && matrix[i][j] != Constants::TREASURE &&
               matrix[i][j] != Constants::MONSTER && matrix[i][j] != Constants::PLAYER && matrix[i][j] != Constants::EXIT){
                validIndexes.push_back(i*width + j);//adding ones so no multiplication by 0
            }
        }
    }
    Shuffle(validIndexes); //what if treasure is more than free tiles?  
    for (size_t i = 0; i < monsterCount; i++)
    {
        matrix[validIndexes[i]/width][validIndexes[i]%width] = Constants::MONSTER;
    }
}
void Map::CreateExit(){ //it is guaranteed that every internal blcok has at least 1 neighbor so ill free the bottom right corner
    matrix[height-1][width-1] = Constants::EXIT;
    matrix[height-2][width-1] = Constants::PATH;
    matrix[height-1][width-2] = Constants::PATH;
    matrix[height-2][width-2] = Constants::PATH;
}
void Map::CreatePlayer(){matrix[0][0] = Constants::PLAYER;}


//rendering
void Map::RenderAll() const{renderer.RenderAll(height, width, matrix, player);};
void Map::RenderStats() const{renderer.RenderStats(height, width, player);}
void Map::RenderMap() const{renderer.RenderMap(height, width, matrix);};
void Map::RenderChunk() const{renderer.RenderChunk(height, width, matrix);};
void Map::RenderPosition(){renderer.RenderPosition(height, width, playerX, playerY, matrix);};
void Map::RenderTile(char c) const{renderer.RenderTile(c);};


//functionality
void Map::MovePlayer(int x, int y){
    int newX = playerX + x;
    int newY = playerY + y;
    if(newX < 0 || newY < 0 || newX > width-1 || newY > height-1)
        return;
    else if(matrix[newY][newX] == Constants::WALL){
        return; 
    }
    //should not render those cases //maybe throw an exception
    else if(matrix[newY][newX] == Constants::TREASURE){
        Event event(this);
        event.TreasureEvent();
    }

    else if(matrix[newY][newX] == Constants::MONSTER)
    {
        Event event(this);
        event.MonsterEvent();
    }
    else if(matrix[newY][newX] == '#'){
        Event event(this);
        event.NextFloor(); return;
    }
    matrix[playerY][playerX] = Constants::PATH;
    matrix[newY][newX] = Constants::PLAYER;
    playerX = newX;
    playerY = newY;
}
