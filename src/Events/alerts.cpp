#include "alerts.h"

void Alerts::Alert(std::ostringstream& msg) {
    std::cout << msg.str() << Constants::padding << '\n';
    GameState::sleepAndIgnoreInputs(3);
}

void Alerts::BattleAlert(std::ostringstream& msg) {
    std::cout << msg.str() << Constants::padding << '\n';
    GameState::sleepAndIgnoreInputs(1);
}