#pragma once
#include "vector"

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
    Map(const unsigned width, const unsigned height, const unsigned monsterCount,const unsigned treasureCount);
    Map(const Map& other);
    Map& operator=(const Map& other);
    ~Map();
    //Rendering
    void Initialize();
    void RenderMap();
    void RenderChunk(const unsigned* ChunkCoords);
    void RenderPosition();
    void RenderTile(char c);
    void CreatePath(const int i, const int j);
    int countVisitedNeighbor(const int i, const int j) const;
    void GenerateMap();
    //functionality
    void CreateTreasure();
    void CreateMonsters();
    void CreatePlayer();
    void CreateExit();
    void MovePlayer(const int x, const int y);
    //events
    void TreasureEvent();
    void MonsterEvent();
    void NextFloor();
private:
    unsigned width, height;
    unsigned playerX, playerY;
    unsigned treasureCount, monsterCount;
    unsigned floor;//not adding it in the constructors, because when creating a
    // map it should be always 0 and when using operator= it should always be trasferred
    std::vector<std::vector<char>> map;
};

struct Point{
    short x, y;
};

