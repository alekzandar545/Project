#include "GameSaver.h"
#include "constants.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip> // For std::put_time
#include <algorithm>
#include <sstream> // For std::stringstream

bool GameSaver::SaveGame(const Player& player, const Map& map, std::string dir) {
    dir += player.GetName() + "_" + GetCurrentDateTimeAsString() + ".bin";
    std::ofstream writer(dir);
    if (!writer.is_open()) {
        throw std::runtime_error(dir + " failed to save file!");
    }

    // Save player data
    SavePlayer(writer, player);

    // Save map data
    SaveMap(writer, map);

    writer.close();
    return true;
}

bool GameSaver::SaveHighscore(const Player& player, std::string dir){
    dir += player.GetName() + "_" + GetCurrentDateTimeAsString() + ".bin";
    std::ofstream writer(dir);
    if (!writer.is_open()) {
        throw std::runtime_error("Failed to save file!");
    }
    // Save player data only
    SavePlayer(writer, player);
    writer.close();
    return true;
}

std::string GameSaver::GetCurrentDateTimeAsString() {
    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    // Convert to local time
    std::tm local_tm = *std::localtime(&now_time);
    
    // Format the time into a string
    std::stringstream ss;
    ss << std::put_time(&local_tm, "%Y-%m-%d_%H-%M-%S"); // Format: YYYY-MM-DD_HH-MM-SS
    return ss.str();
}

void GameSaver::SavePlayer(std::ofstream& writer, const Player& player) {   
    std::string name = player.GetName();
    // need to reformat the name
    std::replace(name.begin(), name.end(), ' ', '_');
    writer << name << " "
           << player.GetStrength() << " "
           << player.GetMana() << " "
           << player.GetMaxHP() << " "
           << player.GetHP() << " "
           << player.GetArmor() << " "
           << player.GetDexterity() << " "
           << player.GetStatPoints() << " "
           << player.GetLevel() << " "
           << player.GetXP() << " "
           << player.GetRequiredXP() << " "
           << player.GetGold() << " "
           << player.GetInventorySize() << '\n';

    const std::vector<Item>& inventory = player.GetInventory();
    for (const Item& item : inventory) {
        SaveItem(writer, item);
    }

    SaveItem(writer, player.GetWeapon());
    SaveItem(writer, player.GetSpell());
    SaveItem(writer, player.GetArmorPiece());

    writer << std::endl;
}

void GameSaver::SaveItem(std::ofstream& writer, const Item& item) {
    std::string name = item.GetName();
    // need to reformat the name
    std::replace(name.begin(), name.end(), ' ', '_');
    writer << static_cast<int>(item.GetType()) << " "
           << name << " "
           << item.GetPower() << '\n';
}

void GameSaver::SaveMap(std::ofstream& writer, const Map& map) {
    const std::vector<std::vector<char>>& matrix = map.GetMatrix();
    writer << map.GetWidth() << " "
           << map.GetHeight() << " "
           << map.GetPlayerX() << " "
           << map.GetPlayerY() << " "
           << map.GetRenderer()->GetChunkX() << " "
           << map.GetRenderer()->GetChunkY() << " "
           << map.GetMonsterCount() << " "
           << map.GetTreasureCount() << " "
           << map.GetFloor() << std::endl;

    for (const std::vector<char>& row : matrix) {
        for (char ch : row) {
            if (ch == Constants::WALL)
                writer << '%';
            else if (ch == Constants::PATH)
                writer << '.';
            else
                writer << ch;
        }
    }
}
