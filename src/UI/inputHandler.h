#pragma once

#include "../Entities/player.h"
#include "../UI/inventoryUI.h"
#include "../UI/statsUI.h"
#include "../UI/startMenuUI.h"
#include "../UI/selectionUI.h"
#include "../Utils/constants.h"
#include "../Utils/gameState.h"
#include "loadGameUI.h"
#include "../Events/combatEvents.h"

class Event;

/**
 * @class InputHandler
 * @brief Handles user input for various UI screens and events.
 * 
 * The InputHandler class provides static methods to handle user input for different UI screens and events in the game.
 * It includes methods for handling input during battles, map navigation, inventory management, stats display,
 * start menu options, race selection, and game loading.
 */
class InputHandler {
public:
    /**
     * @brief Handles user input during battles.
     * 
     * This method takes care of processing user input during battles and updates the necessary variables and UI elements.
     * 
     * @param event A pointer to the CombatEvents object.
     * @param ui The BattleUI object.
     * @param playerIsDead A reference to a boolean variable indicating if the player is dead.
     * @param monsterIsDead A reference to a boolean variable indicating if the monster is dead.
     * @param fled A reference to a boolean variable indicating if the player has fled from the battle.
     */
    static void BattleUserInput(CombatEvents* event, BattleUI& ui, bool& playerIsDead, bool& monsterIsDead, bool& fled);

    /**
     * @brief Handles user input for map navigation.
     * 
     * This method handles user input for navigating the game map and updates the necessary variables and UI elements.
     * 
     * @param map The Map object.
     * @param p The Player object.
     */
    static void UserInput(Map& map, Player& p);

    /**
     * @brief Handles user input for inventory management.
     * 
     * This method handles user input for managing the player's inventory and returns a boolean value indicating if the
     * inventory screen should remain open.
     * 
     * @param ui The InventoryUI object.
     * @return True if the inventory screen should remain open, false otherwise.
     */
    static bool InventoryUserInput(InventoryUI& ui);

    /**
     * @brief Handles user input for displaying player stats.
     * 
     * This method handles user input for displaying the player's stats and returns a boolean value indicating if the
     * stats screen should remain open.
     * 
     * @param ui The StatsUI object.
     * @return True if the stats screen should remain open, false otherwise.
     */
    static bool StatsUserInput(StatsUI& ui);

    /**
     * @brief Handles user input for the start menu options.
     * 
     * This method handles user input for the start menu options and updates the necessary variables and UI elements.
     * 
     * @param ui The StartMenuUI object.
     * @param OpenStartUI A reference to a boolean variable indicating if the start menu UI should remain open.
     * @param newGame A reference to a boolean variable indicating if a new game should be started.
     * @param loadDir A reference to a string variable storing the directory path for loading a saved game.
     */
    static void StartUserInput(StartMenuUI& ui, bool& OpenStartUI, bool& newGame, std::string& loadDir);

    /**
     * @brief Handles user input for race selection.
     * 
     * This method handles user input for selecting the player's race and updates the necessary variables and UI elements.
     * 
     * @param ui The SelectionUI object.
     * @param OpenRaceSelectUI A reference to a boolean variable indicating if the race selection UI should remain open.
     * @param race A reference to a PlayerRace variable storing the selected race.
     */
    static void RaceSelectUserInput(SelectionUI& ui, bool& OpenRaceSelectUI, Player::PlayerRace& race);

    /**
     * @brief Handles user input for loading a saved game.
     * 
     * This method handles user input for loading a saved game and updates the necessary variables and UI elements.
     * 
     * @param ui The LoadGameUI object.
     * @param OpenLoadGameUI A reference to a boolean variable indicating if the load game UI should remain open.
     * @param loadDir A reference to a string variable storing the directory path for loading a saved game.
     */
    static void LoadUserInput(LoadGameUI& ui, bool& OpenLoadGameUI, std::string& loadDir);

private:
};

