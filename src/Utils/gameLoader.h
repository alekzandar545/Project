#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "../Entities/player.h"
#include "../MapGenerator/map.h"
#include "../Items/item.h"

/**
 * @class GameLoader
 * @brief The GameLoader class provides functionality to load and display game data.
 *
 * The GameLoader class contains static methods to load game data, such as player information,
 * high scores, and game maps, from a save file. It also provides a method to display the high scores.
 */
class GameLoader {
public:
    /**
     * @brief Loads the game data from a save file.
     * @param player The reference to the Player object to load the player information into.
     * @param map The reference to the Map object to load the game map into.
     * @param saveFile The path to the save file.
     * @return True if the game data is successfully loaded, false otherwise.
     */
    static bool LoadGame(Player& player, Map& map, const std::string& saveFile);

    /**
     * @brief Displays the high scores.
     *
     * This method displays the high scores of the game.
     */
    static void DisplayHighScores();

private:
    /**
     * @brief Loads the high scores from a file.
     * @param characters The vector of Player objects to load the high scores into.
     */
    static void LoadHighScores(std::vector<Player>& characters);

    /**
     * @brief Loads a player from a file.
     * @param reader The input file stream to read the player data from.
     * @param player The reference to the Player object to load the player information into.
     * @return True if the player data is successfully loaded, false otherwise.
     */
    static bool LoadPlayer(std::ifstream& reader, Player& player);

    /**
     * @brief Loads an item from a file.
     * @param reader The input file stream to read the item data from.
     * @param item The reference to the Item object to load the item information into.
     * @return True if the item data is successfully loaded, false otherwise.
     */
    static bool LoadItem(std::ifstream& reader, Item& item);

    /**
     * @brief Loads a map from a file.
     * @param reader The input file stream to read the map data from.
     * @param map The reference to the Map object to load the map information into.
     * @param player A pointer to the Player object associated with the map.
     * @return True if the map data is successfully loaded, false otherwise.
     */
    static bool LoadMap(std::ifstream& reader, Map& map, Player* player);
};