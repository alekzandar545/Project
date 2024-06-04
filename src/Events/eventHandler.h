#pragma once

#include "../MapGenerator/map.h"
#include "../Utils/constants.h"
#include "../UI/battleUI.h"
#include "../Entities/player.h"
#include "../Entities/monster.h"
#include "../Utils/gameState.h"

/**
 * @class Event
 * @brief Represents an event in the game.
 * 
 * The Event class is responsible for handling various events that can occur in the game.
 * These events include treasure events, monster events, and advancing to the next floor.
 */

class Event{
private:
    const unsigned baseXP = 25; /**< The base experience points gained from the event. */
    const unsigned bonusXP = 3; /**< The bonus experience points gained from the event. */
    const unsigned XPDrop = baseXP + GameState::GetGameMap()->GetFloor() * bonusXP; /**< The total experience points dropped from the event. */
    const unsigned goldDrop = 5 + GameState::GetGameMap()->GetFloor(); /**< The amount of gold dropped from the event. */
public:
    /**
     * @brief Constructs a new Event object.
     * 
     * @param map Pointer to the game map
     */
    Event() = default;

    /**
     * @brief Copy constructor is deleted.
     * 
     * @param other The Event object to be copied
     */
    Event(const Event& other) = default;


    Event& operator=(const Event& other) = default;

    /**
     * @brief Default destructor. 
     */
    ~Event() = default;

    /**
     * @brief Handles a treasure event.
     */
    void TreasureEvent(Map* map);

    /**
     * @brief Handles the game over event.
     */
    void GameOver() const;

    /**
     * @brief Handles a monster attack event.
     * 
     * @param monster Pointer to the monster object
     * @param playerIsDead Reference to a boolean indicating if the player is dead
     */
    void MonsterAttack(Monster* monster, bool& playerIsDead);

    /**
     * @brief Handles a monster event.
     */
    void MonsterEvent(Map* map);

    /**
     * @brief Advances to the next floor.
     */
    void NextFloor(Map* map);
};

