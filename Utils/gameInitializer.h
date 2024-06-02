#pragma once

#include "../Entities/player.h"
#include "../MapGenerator/map.h"

class GameInitializer {
public:
    static Player CreatePlayer();
    static Map CreateMap(Player* player);
    static void NewGame();
    static void LoadGame(const std::string& saveDir);
};