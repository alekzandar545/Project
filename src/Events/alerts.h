#pragma once
#include <sstream>
#include <iostream>
#include "../Utils/constants.h"
#include "../Utils/gameState.h"

/**
 * @class Alerts
 * @brief The Alerts class provides static methods for displaying alerts and battle alerts.
 */
class Alerts{
public:
    /**
     * @brief Displays a general alert message.
     * @param msg The message to be displayed.
     */
    static void Alert(std::ostringstream& msg);

    /**
     * @brief Displays a battle alert message.
     * @param msg The message to be displayed.
     */
    static void BattleAlert(std::ostringstream& msg);
};

