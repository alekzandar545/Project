#pragma once

#include <iostream>
#include "selectionUI.h"
#include "../Entities/player.h"
#include "../Entities/monster.h"
#include "../Utils/constants.h"

static const COORD BATTLE_MENU_SELECT_COORDINATES = {18, 1};
static const unsigned PLAYER_HP_OFFSET = 4;
static const unsigned MONSTER_HP_OFFSET = 53;

/**
 * @class BattleUI
 * @brief Represents the user interface for a battle in the game.
 * 
 * The BattleUI class is a derived class of the SelectionUI class and provides
 * methods for rendering graphics, rendering the UI, and rendering HP bars.
 * It also contains a pointer to a Monster object, as well as vectors for storing
 * player and dragon art.
 */
class BattleUI : public SelectionUI {
public:
    /**
     * @brief Constructs a BattleUI object with the specified Monster.
     * @param monster A pointer to the Monster object associated with the battle.
     */
    BattleUI(Monster* monster);

    BattleUI(const BattleUI& other) = default;

    BattleUI& operator=(const BattleUI& other) = default;

    /**
     * @brief Destructor for the BattleUI class.
     * 
     * This destructor is responsible for cleaning up any resources
     * allocated by the BattleUI class (Monster).
     */
    ~BattleUI() override;

    /**
     * @brief Renders the graphics for the battle UI.
     */
    void RenderGraphics() const;

    /**
     * @brief Renders the battle UI.
     */
    void Render() const override;

    /**
     * @brief Renders the HP bars for the player and the monster.
     */
    void RenderHPBars() const;

    /**
     * @brief Gets the Monster object associated with the battle.
     * @return A pointer to the Monster object.
     */
    Monster* getMonster() const;

private:
    Monster* monster; ///< A pointer to the Monster object associated with the battle.
    std::vector<std::string> playerArt; ///< A vector for storing player art.
    std::vector<std::string> dragonArt; ///< A vector for storing dragon art.
};
