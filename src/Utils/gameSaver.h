#pragma once

#include <string>
#include "../Entities/player.h"
#include "../MapGenerator/map.h"
#include "../Items/item.h"

class GameSaver {
public:
    static bool SaveGame(const Player& player, const Map& map, std::string dir);
    static bool SaveHighscore(const Player& player, std::string dir);
private:
    static std::string GetCurrentDateTimeAsString();
    static void SavePlayer(std::ofstream& writer, const Player& player);
    static void SaveItem(std::ofstream& writer, const Item& item);
    static void SaveMap(std::ofstream& writer, const Map& map);
};