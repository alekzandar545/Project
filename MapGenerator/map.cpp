#include "vector"
#include <iostream>
#include <conio.h> 
#include <cmath>
#include <windows.h>
#include "map.h"

const char BORDER_TOP = 219;//220
const char BORDER_BOTTOM = 219;//223
const char BORDER_SIDE = 219;
const char WALL = 178;
const char PATH = 176;
const char EXIT = '#';
const char MONSTER = 'M';
const char TREASURE = 'T';
const char PLAYER = '@';
//mapsizes
const unsigned STARTING_WIDTH[] = {10,15};
const unsigned STARTING_HEIGHT[] = {10,10};
const unsigned STARTING_TREASURE[] = {2,2};
const unsigned STARTING_MONSTERS[] = {2,3};
const unsigned CHUNK_SIZE[] = {30,10};
unsigned CHUNK_COORDS[] = {0,0};//should integrate this in class
//this goes in the UI class im Guessing
HANDLE CURR_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE); 


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
unsigned Fib(unsigned a, unsigned b, unsigned n){
    if (n == 0) return a;
    if (n == 1) return b;
    unsigned prev = a;
    unsigned curr = b;
    unsigned next;
    for (size_t i = 2; i <= n; ++i) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return next;
}
unsigned Min(const unsigned a, const unsigned b){
    if(a < b)
        return a;
    else
        return b;
}
//big4
Map::Map(){
    width = 0;
    height = 0;
    playerX = 0;
    playerY = 0;
    floor = 0;
}
//don't think i need this when i have the constants :)
Map::Map(const unsigned width, const unsigned height, const unsigned monsterCount, const unsigned treasureCount){
    this->width = width;
    this->height = height;
    this->monsterCount = monsterCount;
    this->treasureCount = treasureCount;
    playerX = 0;
    playerY = 0;
    floor = 0;
}
Map::Map(const Map& other){
    map = other.map;
    height = other.height;
    width = other.width;
    monsterCount = other.monsterCount;
    treasureCount = other.treasureCount;
    playerX = other.playerX;
    playerY = other.playerY;
    floor = other.floor;
}
Map& Map::operator=(const Map& other){
    if(&other == this)
        return *this;
    map = other.map;
    height = other.height;
    width = other.width;
    monsterCount = other.monsterCount;
    treasureCount = other.treasureCount;
    playerX = other.playerX;
    playerY = other.playerY;
    //floor = other.floor;
    return *this;
}
Map::~Map() = default;
//Rendering
void Map::RenderTile(char c){
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
void Map::Initialize(){
    for (int i = 0; i < map.size(); ++i)
        for (int j = 0; j < map[0].size(); ++j)
            map[i][j] = WALL;
    CreatePath(0, 0);
}

void Map::RenderChunk(const unsigned* ChunkCoords){ //should drop the parameter probably
    system("cls");
    
    unsigned chunkX = ChunkCoords[0];
    unsigned chunkY = ChunkCoords[1];
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
            if(map[chunkY-1][i] == WALL)
                std::cout << BORDER_TOP;
            else
                RenderTile(map[chunkY-1][i]);
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
        else if(map[i][chunkX-1] == WALL)
            std::cout << BORDER_SIDE;
        else{
            RenderTile(map[i][chunkX-1]);
        }
        //middle part
        for (size_t j = chunkX; j < chunkX + chunkWidth; j++)
        {
            RenderTile(map[i][j]);
        }
        //right border
        if(chunkX + chunkWidth == width)
            std::cout << BORDER_SIDE;
        else if(map[i][chunkX + chunkWidth] == WALL)
            std::cout << BORDER_SIDE;
        else{
            RenderTile(map[i][chunkX + chunkWidth]);
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
            if(map[chunkY + chunkHeight][i] == WALL)
                std::cout << BORDER_BOTTOM;
            else
                RenderTile(map[chunkY + chunkHeight][i]);
        }    
    }
    std::cout << BORDER_SIDE; 
    std::cout << '\n';
}

void Map::RenderMap(){
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
            RenderTile(map[i][j]);
        }
        std::cout << BORDER_SIDE << '\n';
    }
    //print bottom border
    for (size_t i = 0; i < map[0].size() + 2; i++)
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
void Map::RenderPosition(){
    //loading new chunks
    if(playerX < CHUNK_COORDS[0]){
        CHUNK_COORDS[0] -= CHUNK_SIZE[0];
        RenderChunk(CHUNK_COORDS);
    }
    else if(playerX > CHUNK_COORDS[0]+CHUNK_SIZE[0]-1){
        CHUNK_COORDS[0] += CHUNK_SIZE[0];
        RenderChunk(CHUNK_COORDS); 
    }
    else if(playerY < CHUNK_COORDS[1]){
        CHUNK_COORDS[1] -= CHUNK_SIZE[1];
        RenderChunk(CHUNK_COORDS);
    }
    else if(playerY > CHUNK_COORDS[1]+CHUNK_SIZE[1]-1){
        CHUNK_COORDS[1] += CHUNK_SIZE[1];
        RenderChunk(CHUNK_COORDS); 
    }
    
    COORD startCoord = GetConsoleCursorPosition(CURR_HANDLE);
    //should adjust for chnk offset //also shouldnt render at the ends of chunks
    SetConsoleCursorPosition(CURR_HANDLE, {(short)(playerX+1-CHUNK_COORDS[0]), (short)(playerY+1-CHUNK_COORDS[1])});//center
    RenderTile(map[playerY][playerX]);
    if(playerX > 0 && playerX != CHUNK_COORDS[0]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(playerX-CHUNK_COORDS[0]), (short)(playerY+1-CHUNK_COORDS[1])});//left
        RenderTile(map[playerY][playerX-1]);
    }
    if(playerX+1 < width && playerX+1 != CHUNK_COORDS[0] + CHUNK_SIZE[0]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(playerX+2-CHUNK_COORDS[0]), (short)(playerY+1-CHUNK_COORDS[1])});//right
        RenderTile(map[playerY][playerX+1]);
    }
    if(playerY > 0 && playerY != CHUNK_COORDS[1]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(playerX+1-CHUNK_COORDS[0]), (short)(playerY-CHUNK_COORDS[1])});//down
        RenderTile(map[playerY-1][playerX]);
    }
    if(playerY+1 < height && playerY+1 != CHUNK_COORDS[1] + CHUNK_SIZE[1]){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)(playerX+1-CHUNK_COORDS[0]), (short)(playerY+2-CHUNK_COORDS[1])});//up
        RenderTile(map[playerY+1][playerX]);
    }
    SetConsoleCursorPosition(CURR_HANDLE, startCoord);
}

//Use DFS 
void Map::CreatePath(const int i, const int j){
    int directions[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
    std::vector<unsigned> visitOrder = {0,1,2,3};
    //out of boundary
    if(i < 0 || j < 0 || i >= height || j >= width) return ;
    //visited, go back to the coming direction, return 
    if(map[i][j] == PATH) return ;

    //some neightbors are visited in addition to the coming direction, return
    //this is to avoid circles in maze
    if(countVisitedNeighbor(i, j) > rand() % LABYRYINTH +  1) return ;

    map[i][j] = PATH; // visited

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
        if(map[ni][nj] == PATH) count++;//visited
    }
    return count;
}
void Map::GenerateMap(){
    map.clear();
    std::vector<char> row(width);
    for (int i = 0; i < height; ++i)
    {
        map.push_back(row);
    }
    Initialize();
    CreatePlayer();
    CreateExit();
    CreateTreasure();
    CreateMonsters();
}
//functionality
void Map::CreateTreasure(){
    //store possible indexes in vector and then pick 6 random(after each pick, remove one)
    std::vector<unsigned> validIndexes;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if(map[i][j] != WALL && map[i][j] != TREASURE && map[i][j] != MONSTER && map[i][j] != PLAYER && map[i][j] != EXIT){
                validIndexes.push_back(i*width + j);//adding ones so no multiplication by 0
            }
        }
    }
    Shuffle(validIndexes); //what if treasure is more than free tiles?  
    for (size_t i = 0; i < treasureCount; i++)
    {
        map[validIndexes[i]/width][validIndexes[i]%width] = TREASURE;
    }
}
void Map::CreateMonsters(){
    //store possible indexes in vector and then pick 6 random(after each pick, remove one)
    std::vector<unsigned> validIndexes;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if(map[i][j] != WALL && map[i][j] != TREASURE && map[i][j] != MONSTER && map[i][j] != PLAYER && map[i][j] != EXIT){
                validIndexes.push_back(i*width + j);//adding ones so no multiplication by 0
            }
        }
    }
    Shuffle(validIndexes); //what if treasure is more than free tiles?  
    for (size_t i = 0; i < monsterCount; i++)
    {
        map[validIndexes[i]/width][validIndexes[i]%width] = MONSTER;
    }
}
void Map::CreateExit(){ //it is guaranteed that every internal blcok has at least 1 neighbor so ill free the bottom right corner
    map[height-1][width-1] = EXIT;
    map[height-2][width-1] = PATH;
    map[height-1][width-2] = PATH;
    map[height-2][width-2] = PATH;
}
void Map::CreatePlayer(){map[0][0] = PLAYER;}
void Map::MovePlayer(int x, int y){
    int newX = playerX + x;
    int newY = playerY + y;
    if(newX < 0 || newY < 0 || newX > width-1 || newY > height-1)
        return;
    else if(map[newY][newX] == WALL){
        return;
    }
    //should not render those cases //maybe throw an exception
    else if(map[newY][newX] == TREASURE)
        TreasureEvent();
    else if(map[newY][newX] == MONSTER)
        MonsterEvent();
    else if(map[newY][newX] == '#'){
        NextFloor(); return;
    }
    map[playerY][playerX] = PATH;
    map[newY][newX] = PLAYER;
    playerX = newX;
    playerY = newY;
}
//events
void Map::TreasureEvent(){}
void Map::MonsterEvent(){}
void Map::NextFloor(){
    floor++;
    Map newMap(Fib(STARTING_WIDTH[0],STARTING_WIDTH[1],floor),Fib(STARTING_HEIGHT[0],STARTING_HEIGHT[1],floor),
    Fib(STARTING_MONSTERS[0],STARTING_MONSTERS[1],floor),Fib(STARTING_TREASURE[0],STARTING_TREASURE[1], floor));
    *this = newMap;
    playerX = 0;
    playerY = 0;
    GenerateMap();
    CHUNK_COORDS[0] = 0;
    CHUNK_COORDS[1] = 0;
    RenderChunk(CHUNK_COORDS);
}


