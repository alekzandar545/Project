#pragma once

#include "../MapGenerator/map.h"
#include "../Utils/constants.h"
#include "../UI/battleUI.h"
#include "../Entities/player.h"
#include "../Entities/monster.h"

/**
 * @class Event
 * @brief Represents an event in the game.
 * 
 * The Event class is responsible for handling various events that can occur in the game.
 * These events include treasure events, monster events, and advancing to the next floor.
 */
/**
 * @brief The Event class represents an event in the game.
 * 
 * This class handles various events such as treasure events, monster events, and advancing to the next floor.
 */
class Event{
private:
    Map* map; /**< Pointer to the game map */
public:
    /**
     * @brief Constructs a new Event object.
     * 
     * @param map Pointer to the game map
     */
    Event(Map* map);

    /**
     * @brief Handles a treasure event.
     */
    void TreasureEvent();

    /**
     * @brief Handles the game over event.
     */
    void GameOver() const;

    /**
     * @brief Handles a monster attack event.
     * 
     * @param player Pointer to the player object
     * @param monster Pointer to the monster object
     * @param playerIsDead Reference to a boolean indicating if the player is dead
     */
    void MonsterAttack(Player* player, Monster* monster, bool& playerIsDead);

    /**
     * @brief Handles a monster event.
     */
    void MonsterEvent();

    /**
     * @brief Advances to the next floor.
     */
    void NextFloor();
};

