#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "../Entities/player.h"
#include "../MapGenerator/map.h"
#include "../Items/item.h"

class GameLoader {
public:
    static bool LoadGame(Player& player, Map& map, const std::string& saveFile);
    static void LoadHighScores(std::vector<Player>& characters, const std::string& path);
    static void DisplayHighScores(const std::string& path);

private:
    static bool LoadPlayer(std::ifstream& reader, Player& player);
    static bool LoadItem(std::ifstream& reader, Item& item);
    static bool LoadMap(std::ifstream& reader, Map& map, Player* player);
};