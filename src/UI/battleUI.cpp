#include "battleUI.h"
#include "../Utils/gameState.h"
BattleUI::BattleUI( Monster* monster) : SelectionUI(BATTLE_MENU_SELECT_COORDINATES),
                                                         monster(monster) {
    if (GameState::GetGamePlayer() == nullptr || monster == nullptr) {
        throw std::invalid_argument("Player or monster is nullptr");
    }
    SetOptions({"Melee attack", "Spell attack", "Potion", "Flee"});
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
        " ",
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
}

BattleUI::~BattleUI() {
    delete monster;
}

void BattleUI::RenderGraphics() const {
    SetConsoleCursorPosition(CURR_HANDLE, {0, 0});
    for (unsigned i = 0; i < dragonArt.size(); i++) {
        std::cout << playerArt[i] << dragonArt[i] << '\n';
    }
}

void BattleUI::Render() const {
    for (size_t i = 0; i < options.size(); i++) {
        SetConsoleCursorPosition(CURR_HANDLE, {CONSOLE_COORDS.X, (short)(CONSOLE_COORDS.Y + i)});
        if (i == selectionIndex) {
            SetConsoleTextAttribute(CURR_HANDLE, Constants::SELECTED_COLOR);
            std::cout << options[i] << '\n';
            SetConsoleTextAttribute(CURR_HANDLE, Constants::DEFAULT_COLOR);
            continue;
        }
        std::cout << options[i] << '\n';
    }
    RenderHPBars();
}

void BattleUI::RenderHPBars() const {
    SetConsoleTextAttribute(CURR_HANDLE, Constants::RED);
    SetConsoleCursorPosition(CURR_HANDLE, {PLAYER_HP_OFFSET, (short)(dragonArt.size())});
    std::cout << "HP: " << GameState::GetGamePlayer()->GetHP() << '/' << GameState::GetGamePlayer()->GetMaxHP() 
    << "     ";
    SetConsoleTextAttribute(CURR_HANDLE, Constants::BLUE);
    std::cout << "Armor: " << GameState::GetGamePlayer()->GetArmor() << '%' << Constants::padding; //add some padding for shrinking numbers
    SetConsoleTextAttribute(CURR_HANDLE, Constants::RED);
    SetConsoleCursorPosition(CURR_HANDLE, {MONSTER_HP_OFFSET, (short)(dragonArt.size())});
    std::cout << "HP: " << monster->GetHP() << '/' << monster->GetMaxHP() << "     ";
    SetConsoleTextAttribute(CURR_HANDLE, Constants::BLUE);
    std::cout << "Armor: " << monster->GetArmor() << '%' << Constants::padding << '\n';
    SetConsoleTextAttribute(CURR_HANDLE, Constants::DEFAULT_COLOR);
}

Monster* BattleUI::getMonster() const {
    return this->monster;
}