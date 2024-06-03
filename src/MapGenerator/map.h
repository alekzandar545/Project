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
    //Big4
    Map();
    Map(Player* player);
    Map(const unsigned width, const unsigned height, const unsigned monsterCount,
        const unsigned treasureCount, const unsigned floor, Player* player);
    Map(const unsigned width, const unsigned height, const unsigned PlayerX, const unsigned PlayerY, 
        const unsigned monsterCount, const unsigned treasureCount, const unsigned floor, 
        std::vector<std::vector<char>> matrix, Player* player);
    Map(const Map& other);
    Map(Map&& other) noexcept;
    Map& operator=(const Map& other);
    Map& operator=(Map&& other) noexcept;
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
    //getters
    unsigned GetWidth() const;
    unsigned GetHeight() const;
    unsigned GetPlayerX() const;
    unsigned GetPlayerY() const;
    unsigned GetFloor() const;
    Player* GetPlayer() const;
    std::vector<std::vector<char>> GetMatrix() const;
    unsigned GetMonsterCount() const;
    unsigned GetTreasureCount() const;
    Renderer* GetRenderer() const;
    //setters
    void SetPlayer(Player* player);
    void SetWidth(const unsigned width);
    void SetHeight(const unsigned height);
    void SetPlayerX(const unsigned playerX);
    void SetPlayerY(const unsigned playerY);
    void IncreaseFloor();
//private:
    Renderer* renderer;
    unsigned width, height;
    unsigned playerX, playerY;
    unsigned treasureCount, monsterCount;
    unsigned floor;//not adding it in the constructors, because when creating a
    // map it should be always 0 and when using operator= it should always be trasferred
    std::vector<std::vector<char>> matrix;
    //store info for the player
    Player* player;
};
