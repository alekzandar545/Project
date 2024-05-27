#pragma once
#include <iostream>
#include <cstring>
#include "selectionUI.h"
#include "../constants.h"
#include "../Entities/player.h"

static const COORD STATS_SELECT_COORDINATES = {0, 0};
//maybe singleton?
class StatsUI : public SelectionUI{
public:
    StatsUI(Player* player) : SelectionUI(STATS_SELECT_COORDINATES){
        this->player = player;
        SetOptions({"Strength", "Mana", "Health Points", "Dexterity"});
    }
    void Render() const override{
        SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, CONSOLE_COORDS.Y});
        std::cout << "Stats:\n";
        const unsigned offsetY = 2; // for stats line
        for (size_t i = 0; i < options.size(); i++)
        {
            SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, (short)(CONSOLE_COORDS.Y + i + offsetY)});
            if(i==selectionIndex)
                SetConsoleTextAttribute(CURR_HANDLE, 22);
            std::cout << '+' << options[i];
            if(options[i] == "Strength")
                std::cout << " - " << player->str;
            else if(options[i] == "Mana")
                std::cout << " - " << player->mana;
            else if(options[i] == "Health Points")
                std::cout << " - " << player->maxHP;
            else if(options[i] == "Dexterity")
                std::cout << " - " << player->dexterity;
            std::cout <<'\n';
            SetConsoleTextAttribute(CURR_HANDLE, 8);
        }
        std::cout << "\nSpare points: " << player->statPoints << padding;
    }
    //getters
    Player* GetPlayer() const{
        return player;
    }

private:
    Player* player;
};
