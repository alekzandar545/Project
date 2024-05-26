#pragma once
#include <iostream>
#include "selectionUI.h"
#include "../Entities/player.h"
#include "../Entities/monster.h"

static const COORD BATTLE_MENU_SELECT_COORDINATES = {18, 1};
static const unsigned PLAYER_HP_OFFSET = 10;
static const unsigned MONSTER_HP_OFFSET = 60;
//maybe singleton?
class BattleUI : public SelectionUI{
public:
    BattleUI(Player player, Monster monster) : SelectionUI(BATTLE_MENU_SELECT_COORDINATES){
        this->player = &player;
        this->monster = &monster;
        playerArt = {
            "  / \\                  ",
            "  | |                   ",
            "  |.|                   ",
            "  |.|                   ",
            "  |:|      __           ",
            ",_|:|_,   /  )          ",
            "  (Oo    / _I_          ",
            "   +\\ \\  || __|       ",
            "      \\ \\||___|       ",
            "        \\ /.:.\\-\\    ",
            "         |.:. /-----\\  ",
            "         |___|::oOo::|  ",
            "         /   |:<_T_>:|  ",
            "        |_____\\ ::: /  ",
            "         | |  \\ \\:/   ",
            "         | |   | |      ",
            "         \\ /   | \\___ ",
            "         / |   \\_____\\",
            "         `-'"
        };
        dragonArt = {
            " "
            "                                             __----~~~~~~~~~~~------___",
            "                                  .  .   ~~//====......          __--~ ~~",
            "                  -.            \\_|//     |||\\\\  ~~~~~~::::... /~",
            "               ___-==_       _-~o~  \\/    |||  \\\\            _/~~-",
            "       __---~~~.==~||\\=_    -_--~/_-~|-   |\\\\   \\\\        _/~",
            "   _-~~     .=~    |  \\\\-_    '-~7  /-   /  ||    \\      /",
            " .~       .~       |   \\\\ -_    /  /-   /   ||      \\   /",
            "/  ____  /         |     \\\\ ~-_/  /|- _/   .||       \\ /",
            "|~~    ~~|--~~~~--_ \\     ~==-/   | \\~--===~~        .\\",
            "         '         ~-|      /|    |-~\\~~       __--~~",
            "                     |-~~-_/ |    |   ~\\_   _-~            /\\",
            "                          /  \\     \\__   \\/~                \\__",
            "                      _--~ _/ | .-~~____--~-/                  ~~==.",
            "                     ((->/~   '.|||' -_|    ~~-/ ,              . _||",
            "                                -_     ~\\      ~~---l__i__i__i--~~_/",
            "                                _-~-__   ~)  \\--______________--~~",
            "                              //.-~~~-~_--~- |-------~~~~~~~~",
            "                                     //.-~~~--\\"
        };
        for(unsigned i = 0; i < dragonArt.size(); i++){
            std::cout << playerArt[i] << dragonArt[i] << '\n';
        }
    }

    void Render() const override{
        for (size_t i = 0; i < options.size(); i++)
        {
            SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, (short)(CONSOLE_COORDS.Y + i)});
            if(i==selectionIndex){
                SetConsoleTextAttribute(CURR_HANDLE, 22);
                std::cout << options[i] << '\n';
                SetConsoleTextAttribute(CURR_HANDLE, 8);
                continue;
            }
            std::cout << options[i] << '\n';
        }
        RenderHPBars();
    }
    void RenderHPBars() const{
        SetConsoleTextAttribute(CURR_HANDLE, 12);
        SetConsoleCursorPosition(CURR_HANDLE, {PLAYER_HP_OFFSET, (short)(dragonArt.size())});
        std::cout << "HP: " << player->HP << '/' << player->maxHP << "                     "; //add some padding for shrinking numbers
        SetConsoleCursorPosition(CURR_HANDLE, {MONSTER_HP_OFFSET, (short)(dragonArt.size())});
        std::cout << "HP: " << monster->HP << '/' << monster->maxHP << "                   ";
        SetConsoleTextAttribute(CURR_HANDLE, 8);
    }

    Player* getPlayer() const{return this->player;}
    Monster* getMonster() const{return this->monster;}
private:
    Player* player;
    Monster* monster;
    std::vector<std::string> playerArt;
    std::vector<std::string> dragonArt;
};
