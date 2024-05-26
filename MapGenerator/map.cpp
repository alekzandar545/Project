#include "vector"
#include <iostream>
#include <conio.h> 
#include <cmath>
#include <windows.h>
#include "map.h"
#include "constants.h"
#include "../UI/selectionUI.h"
#include "../UI/battleUI.h"
#include "../Entities/player.h"
#include "../Entities/monster.h"
#include <sstream> //move to events later

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

//big4
Map::Map(Player* player){
    width = 0;
    height = 0;
    playerX = 0;
    playerY = 0;
    floor = 0;
    this->player = player;
}
//don't think i need this when i have the constants :)
Map::Map(const unsigned width, const unsigned height, const unsigned monsterCount, const unsigned treasureCount, Player* player){
    this->width = width;
    this->height = height;
    this->monsterCount = monsterCount;
    this->treasureCount = treasureCount;
    playerX = 0;
    playerY = 0;
    floor = 0;
    this->player = player;
}
Map::Map(const Map& other){
    matrix = other.matrix;
    height = other.height;
    width = other.width;
    monsterCount = other.monsterCount;
    treasureCount = other.treasureCount;
    playerX = other.playerX;
    playerY = other.playerY;
    floor = other.floor;
    player = other.player;
}
Map& Map::operator=(const Map& other){
    if(&other == this)
        return *this;
    matrix = other.matrix;
    height = other.height;
    width = other.width;
    monsterCount = other.monsterCount;
    treasureCount = other.treasureCount;
    playerX = other.playerX;
    playerY = other.playerY;
    player = other.player;
    //renderer = other.renderer;
    //floor = other.floor;
    return *this;
}
Map::~Map() = default;

//Creation
void Map::Initialize(){
    for (int i = 0; i < matrix.size(); ++i)
        for (int j = 0; j < matrix[0].size(); ++j)
            matrix[i][j] = WALL;
    CreatePath(0, 0);
}
void Map::CreatePath(const int i, const int j){ //Use DFS 
    int directions[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
    std::vector<unsigned> visitOrder = {0,1,2,3};
    //out of boundary
    if(i < 0 || j < 0 || i >= height || j >= width) return ;
    //visited, go back to the coming direction, return 
    if(matrix[i][j] == PATH) return ;

    //some neightbors are visited in addition to the coming direction, return
    //this is to avoid circles in maze
    if(countVisitedNeighbor(i, j) > rand() % LABYRYINTH +  1) return ;

    matrix[i][j] = PATH; // visited

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
        if(matrix[ni][nj] == PATH) count++;//visited
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
            if(matrix[i][j] != WALL && matrix[i][j] != TREASURE && matrix[i][j] != MONSTER && matrix[i][j] != PLAYER && matrix[i][j] != EXIT){
                validIndexes.push_back(i*width + j);//adding ones so no multiplication by 0
            }
        }
    }
    Shuffle(validIndexes); //what if treasure is more than free tiles?  
    for (size_t i = 0; i < treasureCount; i++)
    {
        matrix[validIndexes[i]/width][validIndexes[i]%width] = TREASURE;
    }
}
void Map::CreateMonsters(){
    //store possible indexes in vector and then pick 6 random(after each pick, remove one)
    std::vector<unsigned> validIndexes;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if(matrix[i][j] != WALL && matrix[i][j] != TREASURE && matrix[i][j] != MONSTER && matrix[i][j] != PLAYER && matrix[i][j] != EXIT){
                validIndexes.push_back(i*width + j);//adding ones so no multiplication by 0
            }
        }
    }
    Shuffle(validIndexes); //what if treasure is more than free tiles?  
    for (size_t i = 0; i < monsterCount; i++)
    {
        matrix[validIndexes[i]/width][validIndexes[i]%width] = MONSTER;
    }
}
void Map::CreateExit(){ //it is guaranteed that every internal blcok has at least 1 neighbor so ill free the bottom right corner
    matrix[height-1][width-1] = EXIT;
    matrix[height-2][width-1] = PATH;
    matrix[height-1][width-2] = PATH;
    matrix[height-2][width-2] = PATH;
}
void Map::CreatePlayer(){matrix[0][0] = PLAYER;}


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
    else if(matrix[newY][newX] == WALL){
        return; 
    }
    //should not render those cases //maybe throw an exception
    else if(matrix[newY][newX] == TREASURE)
        TreasureEvent();
    else if(matrix[newY][newX] == MONSTER)
        MonsterEvent();
    else if(matrix[newY][newX] == '#'){
        NextFloor(); return;
    }
    matrix[playerY][playerX] = PATH;
    matrix[newY][newX] = PLAYER;
    playerX = newX;
    playerY = newY;
}
//events --> event handler?
void Map::TreasureEvent(){
    player->AddGold(5+floor);
}

void Map::Alert(std::ostringstream& msg) const{
    std::string padding = "                    ";
    std::cout <<'\n' << msg.str() << padding;
    _getch();
}
void Map::BattleAlert(std::ostringstream& msg) const{
    std::string padding = "                    ";
    std::cout << '\n' << msg.str() << padding;
}

void Map::GameOver() const{
   system("cls"); 
   std::cout << "";
}

void Map::BattleUserInput(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead, bool& evaded) 
{ 
    // Checks if a key is pressed or not 
    if (_kbhit()) { 
        // Getting the pressed key 
        int ch = _getch(); 
        switch (ch) { 
            case 'w': //up arrow
                ui.MoveSeleciton(0);
                break; 
            case 's': //down arrow
                ui.MoveSeleciton(1);
                break; 
            case 'e':
                switch (ui.GetSelectionIndex())
                {
                case 0: //add enum for those
                    if(ui.getPlayer()->MeleeAttack(*ui.getMonster())){
                        ui.Render(); 
                        std::ostringstream msg;
                        msg << ui.getPlayer()->GetName() << " has slain the dragon"<<
                                                            " and has earned " << std::to_string(5+floor)  
                                                            << " gold and " << std::to_string(25+floor*3) 
                                                            << " xp" << '\n' << "Press any key to continue";
                        Alert(msg);
                        monsterIsDead = true;
                        return;
                    }
                    else{
                        ui.Render(); 
                        std::ostringstream msg; 
                        msg << ui.getPlayer()->GetName() << " hit the dragon with a " << ui.getPlayer()->weapon.GetName();
                        BattleAlert(msg);
                    }
                    break;
                case 1: //move this logic to a functionc
                    if(ui.getPlayer()->SpellAttack(*ui.getMonster())){
                        ui.Render(); 
                        std::ostringstream msg;
                        msg << ui.getPlayer()->GetName() << " has slain the dragon"<<
                                                            " and has earned " << std::to_string(5+floor)  
                                                            << " gold and " << std::to_string(25+floor*3) 
                                                            << " xp" << '\n' << "Press any key to continue";
                        Alert(msg);
                        monsterIsDead = true;
                        return;
                    }
                    else{
                        ui.Render(); 
                        std::ostringstream msg; 
                        msg << ui.getPlayer()->GetName() << " cast a " << ui.getPlayer()->spell.GetName() << " on the dragon!";
                        BattleAlert(msg);
                    }
                    break;
                case 2:
                    //potion logic
                    break;
                case 3:
                    evaded = true;
                    break;
                }
                break;
                ui.Render();
        } 
    } 
} 
void Map::MonsterEvent(){
    system("cls");
    Monster m(floor); //monsters get stronger on each floor
    BattleUI battle(*player, m);
    battle.SetOptions({"Melee attack", "Spell attack", "Potion", "Evade"});
    battle.Render();
    bool playerIsDead = 0;
    bool monsterIsDead = 0;
    bool evaded = 0;
    while(!playerIsDead && !monsterIsDead && !evaded){
        BattleUserInput(battle, playerIsDead, monsterIsDead, evaded);
    }
    if(playerIsDead){
        GameOver();
        return;
    }
    else if(monsterIsDead){
        player->AddGold(5+floor); // more gold on each floor
        player->AddXP(25+floor*3); //more xp on each floor
        //player->AddItem(GetRandomItem(floor)); //stronger items on each floor
    }
    system("cls");
    RenderAll();
}


void Map::NextFloor(){
    system("cls");
    floor++;
    Map newMap(Fib(STARTING_WIDTH[0],STARTING_WIDTH[1],floor),Fib(STARTING_HEIGHT[0],STARTING_HEIGHT[1],floor),
    Fib(STARTING_MONSTERS[0],STARTING_MONSTERS[1],floor),Fib(STARTING_TREASURE[0],STARTING_TREASURE[1], floor), player);
    newMap.GenerateMap();
    *this = newMap;
    playerX = 0;
    playerY = 0;
    renderer.SetChunkX(0); //maybe problematic later
    renderer.SetChunkY(0); 
    RenderAll();
}


