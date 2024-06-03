#pragma once

#include <string>
#include "../Entities/player.h"
#include "../MapGenerator/map.h"
#include "../Items/item.h"

/**
 * @class GameSaver
 * @brief The GameSaver class provides static methods to save game data and highscores.
 */
class GameSaver {
public:
    /**
     * @brief Saves the game data including the player and map information to a specified directory.
     * @param player The player object to be saved.
     * @param map The map object to be saved.
     * @param dir The directory path where the game data will be saved.
     * @return True if the game data is successfully saved, false otherwise.
     */
    static bool SaveGame(const Player& player, const Map& map, std::string dir);

    /**
     * @brief Saves the player's highscore to a specified directory.
     * @param player The player object whose highscore will be saved.
     * @param dir The directory path where the highscore will be saved.
     * @return True if the highscore is successfully saved, false otherwise.
     */
    static bool SaveHighscore(const Player& player, std::string dir);

private:
    /**
     * @brief Gets the current date and time as a string.
     * @return The current date and time as a string in the format "YYYY-MM-DD HH:MM:SS".
     */
    static std::string GetCurrentDateTimeAsString();

    /**
     * @brief Saves the player object to the output stream.
     * @param writer The output stream to save the player object to.
     * @param player The player object to be saved.
     */
    static void SavePlayer(std::ofstream& writer, const Player& player);

    /**
     * @brief Saves the item object to the output stream.
     * @param writer The output stream to save the item object to.
     * @param item The item object to be saved.
     */
    static void SaveItem(std::ofstream& writer, const Item& item);

    /**
     * @brief Saves the map object to the output stream.
     * @param writer The output stream to save the map object to.
     * @param map The map object to be saved.
     */
    static void SaveMap(std::ofstream& writer, const Map& map);
};