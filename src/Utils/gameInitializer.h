#pragma once

#include "../Entities/player.h"
#include "../MapGenerator/map.h"

/**
 * @class GameInitializer
 * @brief The GameInitializer class provides methods for initializing and managing the game.
 */
class GameInitializer {
public:
    /**
     * @brief Creates a new player.
     * @param player The player object to be created.
     */
    static void CreatePlayer(Player& player);

    /**
     * @brief Creates a new map based on the player's information.
     * @param player The player object used to generate the map.
     * @return The generated map.
     */
    static Map CreateMap(Player* player);

    /**
     * @brief Starts a new game.
     */
    static void NewGame();

    /**
     * @brief Loads a saved game from the specified directory.
     * @param saveDir The directory where the saved game is located.
     */
    static void LoadGame(const std::string& saveDir);
};