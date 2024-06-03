#pragma once
#include "../UI/battleUI.h"
#include "alerts.h"

/**
 * @class CombatEvents
 * @brief Handles combat-related events in the game.
 */
class CombatEvents{
public:
    /**
     * @brief Constructs a CombatEvents object.
     * @param map A pointer to the game map.
     */
    CombatEvents(Map* map);

    /**
     * @brief Drops a potion for the player.
     * @param player The player object.
     */
    void DropPotion(Player& player);

    /**
     * @brief Handles a melee attack in combat.
     * @param ui The battle user interface.
     * @param playerIsDead A boolean indicating if the player is dead.
     * @param monsterIsDead A boolean indicating if the monster is dead.
     */
    void HandleMeleeAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead);

    /**
     * @brief Handles a spell attack in combat.
     * @param ui The battle user interface.
     * @param playerIsDead A boolean indicating if the player is dead.
     * @param monsterIsDead A boolean indicating if the monster is dead.
     */
    void HandleSpellAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead);

    /**
     * @brief Handles the usage of a potion in combat.
     * @param ui The battle user interface.
     */
    void HandlePotionUsage(BattleUI& ui);

    /**
     * @brief Handles the player's attempt to flee from combat.
     * @param ui The battle user interface.
     * @param fled A boolean indicating if the player successfully fled.
     */
    void HandleFlee(BattleUI& ui, bool& fled);

private:
    Map* map; ///< A pointer to the game map.
};