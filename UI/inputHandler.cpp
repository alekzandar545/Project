#include "inputHandler.h"

InputHandler::InputHandler(Event* event) {this->event = event;}

void InputHandler::UserInput(Map& map, Player& player, bool& isGameOver) {
    if (_kbhit()) {
        int ch = _getch();
        switch (ch) {
            case 'a':
                map.MovePlayer(-1, 0);
                if(!isGameOver){
                    map.RenderStats();
                    map.RenderPosition();
                }
                break;
            case 'd':
                map.MovePlayer(1, 0);
                if(!isGameOver){
                    map.RenderStats();
                    map.RenderPosition();
                }
                break;
            case 'w':
                map.MovePlayer(0, -1);
                if(!isGameOver){
                    map.RenderStats();
                    map.RenderPosition();
                }
                break;
            case 's':
                map.MovePlayer(0, 1);
                if(!isGameOver){
                    map.RenderStats();
                    map.RenderPosition();
                }
                break;
            case 'i': {
                system("cls");
                InventoryUI ui(&player);
                bool isOpen = true;
                ui.Render();
                while (isOpen) {
                    isOpen = InventoryUserInput(ui);
                }
                system("cls");
                map.RenderAll();
                break;
            }
            case 'g': {
                system("cls");
                StatsUI ui(&player);
                bool isOpen = true;
                ui.Render();
                while (isOpen) {
                    isOpen = StatsUserInput(ui);
                }
                system("cls");
                map.RenderAll();
                break;
            }
            case 'x':
                GameSaver::SaveGame(player, map);
                isGameOver = true;
                system("cls");
                break;
        }
    }
}

bool InputHandler::InventoryUserInput(InventoryUI& ui) {
    if (_kbhit()) {
        int ch = _getch();
        switch (ch) {
            case 'w':
                ui.MoveSelection(0);
                break;
            case 's':
                ui.MoveSelection(1);
                break;
            case 'e':
                try{
                    ui.GetPlayer()->EquipItem(ui.GetSelectionIndex());
                }
                catch(const std::out_of_range& e){
                    std::cerr <<'\n'<< e.what();
                }
                ui.Render();
                break;
            case 'x':
                try{
                    ui.GetPlayer()->SellItem(ui.GetSelectionIndex());
                }
                catch(const std::out_of_range& e){
                    std::cerr <<'\n'<< e.what();
                }
                system("cls");
                ui.CheckSold();
                ui.Render();
                break;
            case 'i':
                return false;
        }
    }
    return true;
}

bool InputHandler::StatsUserInput(StatsUI& ui) {
    if (_kbhit()) {
        int ch = _getch();
        switch (ch) {
            case 'w':
                ui.MoveSelection(0);
                break;
            case 's':
                ui.MoveSelection(1);
                break;
            case 'e':
                if (ui.GetOption(ui.GetSelectionIndex()) == "Strength")
                    ui.GetPlayer()->AddStrength();
                else if (ui.GetOption(ui.GetSelectionIndex()) == "Mana")
                    ui.GetPlayer()->AddMana();
                else if (ui.GetOption(ui.GetSelectionIndex()) == "Health Points")
                    ui.GetPlayer()->AddHP();
                else if (ui.GetOption(ui.GetSelectionIndex()) == "Dexterity")
                    ui.GetPlayer()->AddDexterity();
                ui.Render();
                break;
            case 'g':
                return false;
        }
    }
    return true;
}

void InputHandler::StartUserInput(StartMenuUI& ui, bool& OpenStartUI, bool& newGame, std::string& loadDir, bool& isGameOver){
    if (_kbhit()) {
        int ch = _getch();
        switch (ch) {
            case 'w':
                ui.MoveSelection(0);
                break;
            case 's':
                ui.MoveSelection(1);
                break;
            case 'e':
                switch (ui.GetSelectionIndex()) {
                    case 0: //new game
                        OpenStartUI = false;
                        newGame = true                                                  ;
                        break;
                    case 1:{ //load game              
                        LoadGameUI loadUI("Saves");
                        //check if empty
                        if(loadUI.GetOptions().size() == 0)
                            return;
                        system("cls");
                        bool OpenLoadUI = true;
                        loadUI.Render();
                        while(OpenLoadUI){
                            LoadUserInput(loadUI, OpenLoadUI, loadDir);
                        }
                        system("cls");
                        OpenStartUI = false;
                        break;
                    }
                    case 2:
                        // highscores interface
                        break;
                    case 3:
                        isGameOver = true;
                        OpenStartUI = false;
                        system("cls");
                        break;
                }
                break;
        }
    }
}

void InputHandler::LoadUserInput(LoadGameUI& ui, bool& OpenLoadGameUI, std::string& loadDir){
    if (_kbhit()) {
        int ch = _getch();
        switch (ch) {
            case 'w':
                ui.MoveSelection(0);
                break;
            case 's':
                ui.MoveSelection(1);
                break;
            case 'e':
                std::string dirName = "Saves/";
                dirName.append(ui.GetOption(ui.GetSelectionIndex()));
                loadDir = dirName;
                OpenLoadGameUI = false;
                system("cls");
                break;
        }
    }
}

void InputHandler::RaceSelectUserInput(SelectionUI& ui, bool& OpenRaceSelectUI, Player::PlayerRace& race) {
    if (_kbhit()) {
        int ch = _getch();
        switch (ch) {
            case 'w':
                ui.MoveSelection(0);
                break;
            case 's':
                ui.MoveSelection(1);
                break;
            case 'e':
                switch (ui.GetSelectionIndex()) {
                    case 0:
                        race = Player::PlayerRace::Human;
                        break;
                    case 1:
                        race = Player::PlayerRace::Sorcerer;
                        break;
                    case 2:
                        race = Player::PlayerRace::Berserk;
                        break;
                    default:
                        race = Player::PlayerRace::Human;
                        break;
                }
                OpenRaceSelectUI = false;
                system("cls");
                break;
        }
    }
}

void InputHandler::BattleUserInput(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead, bool& fled) {
    if (_kbhit()) {
        int ch = _getch();
        switch (ch) {
            case 'w':
                ui.MoveSelection(0);
                break;
            case 's':
                ui.MoveSelection(1);
                break;
            case 'e':
                switch (ui.GetSelectionIndex()) {
                    case 0:
                        event->HandleMeleeAttack(ui, playerIsDead, monsterIsDead);
                        break;
                    case 1:
                        event->HandleSpellAttack(ui, playerIsDead, monsterIsDead);
                        break;
                    case 2:
                        event->HandlePotionUsage(ui);
                        break;
                    case 3:
                        event->HandleFlee(ui, fled);
                        break;
                }
                break;
        }
        ui.Render();
    }
}