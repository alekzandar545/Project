#include "StatsUI.h"
#include "../Utils/constants.h" 
#include "../Utils/gameState.h"
const COORD StatsUI::STATS_SELECT_COORDINATES = {0,0};

StatsUI::StatsUI() : SelectionUI(STATS_SELECT_COORDINATES) {
    SetOptions({"Strength", "Mana", "Health Points", "Dexterity"});
}

void StatsUI::Render() const {
    SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, CONSOLE_COORDS.Y});
    std::cout << "Stats:\n";
    const unsigned offsetY = 2; // for stats line
    for (size_t i = 0; i < options.size(); i++) {
        SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, (short)(CONSOLE_COORDS.Y + i + offsetY)});
        if(i == selectionIndex)
            SetConsoleTextAttribute(CURR_HANDLE, 22);
        std::cout << '+' << options[i];
        if(options[i] == "Strength")
            std::cout << " - " << GameState::GetGamePlayer()->GetStrength();
        else if(options[i] == "Mana")
            std::cout << " - " << GameState::GetGamePlayer()->GetMana();
        else if(options[i] == "Health Points")
            std::cout << " - " << GameState::GetGamePlayer()->GetMaxHP();
        else if(options[i] == "Dexterity")
            std::cout << " - " << GameState::GetGamePlayer()->GetDexterity();
        std::cout << '\n';
        SetConsoleTextAttribute(CURR_HANDLE, 8);
    }
    std::cout << "\nSpare points: " << GameState::GetGamePlayer()->GetStatPoints() << Constants::padding;
}

