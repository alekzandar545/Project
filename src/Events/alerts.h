#pragma once
#include <sstream>
#include <iostream>
#include "../Utils/constants.h"
#include "../Utils/gameState.h"

class Alerts{
public:
    static void Alert(std::ostringstream& msg);
    static void BattleAlert(std::ostringstream& msg);
};

