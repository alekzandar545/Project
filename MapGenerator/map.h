#pragma once
#include "vector"
#include "../Entities/player.h"
#include "renderer.h"
#include "../UI/selectionUI.h"
#include "../UI/battleUI.h"
class Map{
public:
    enum ObstacleDensity{ //am thinking of adding an option to pick this when starting the game
        LABYRYINTH = 1,
        HIGH_DENSITY = 2,
        MEDIUM_DENSITY = 3,
        LOW_DENSITY = 4
    };
    //getters
    unsigned GetWidth() const{return this->width;}
    unsigned GetHeight() const{return this->height;}
    unsigned GetPlayerX() const{return this->playerX;}
    unsigned GetPlayerY() const{return this->playerY;}
    std::vector<std::vector<char>>& GetMap() {return this->matrix;}
    //setters
    void SetWidth(const unsigned width){this->width = width;}
    void SetHeight(const unsigned height){this->height = height;}
    void SetPlayerX(const unsigned playerX){this->playerX = playerX;}
    void SetPlayerY(const unsigned playerY){this->playerY = playerY;}
    //Big4
    Map(Player* player);
    Map(const unsigned width, const unsigned height, const unsigned monsterCount,const unsigned treasureCount, Player* player);
    Map(const Map& other);
    Map& operator=(const Map& other);
    ~Map();
    //creation
    void Initialize();
    void CreatePath(const int i, const int j);
    int countVisitedNeighbor(const int i, const int j) const;
    void GenerateMap();
    void CreateTreasure();
    void CreateMonsters();
    void CreatePlayer();
    void CreateExit();
    //rendering
    void RenderAll() const;
    void RenderStats() const;
    void RenderMap() const;
    void RenderChunk() const;
    void RenderPosition();
    void RenderTile(char c) const;
    //functionality
    void MovePlayer(const int x, const int y);
    //events
    void TreasureEvent();
    void MonsterEvent();
    void NextFloor();
    void Alert(std::ostringstream& msg) const;
    void BattleAlert(std::ostringstream& msg) const;
    void GameOver() const;
    void BattleUserInput(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead, bool& evaded);
private:
    Renderer renderer;
    unsigned width, height;
    unsigned playerX, playerY;
    unsigned treasureCount, monsterCount;
    unsigned floor;//not adding it in the constructors, because when creating a
    // map it should be always 0 and when using operator= it should always be trasferred
    std::vector<std::vector<char>> matrix;
    //store info for the player
    Player* player;
};

struct Point{
    short x, y;
};

