#include "inputHandler.h"
#include "../Events/eventHandler.h"
#include <conio.h>
#include <windows.h>
#include "../Utils/gameSaver.h"
#include "../Utils/gameLoader.h"

InputHandler::InputHandler() = default;

void InputHandler::UserInput(Map& map, Player& player) {
    if (_kbhit() && !GameState::isGameOver && !GameState::isSleeping) {
        int ch = _getch();
        switch (ch) {
            case 'a':
                map.MovePlayer(-1, 0);
                if(!GameState::isGameOver){
                    map.RenderStats();
                    map.RenderPosition();
                }
                break;
            case 'd':
                map.MovePlayer(1, 0);
                if(!GameState::isGameOver){
                    map.RenderStats();
                    map.RenderPosition();
                }
                break;
            case 'w':
                map.MovePlayer(0, -1);
                if(!GameState::isGameOver){
                    map.RenderStats();
                    map.RenderPosition();
                }
                break;
            case 's':
                map.MovePlayer(0, 1);
                if(!GameState::isGameOver){
                    map.RenderStats();
                    map.RenderPosition();
                }
                break;
            case 'i': {
                system("cls");
                InventoryUI ui;
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
                StatsUI ui;
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
                if(GameSaver::SaveGame(player, map, "../Saves/")){
                    system("cls");
                    GameState::EndGame();   
                    return;
                }
                break;
        }
    }
}

bool InputHandler::InventoryUserInput(InventoryUI& ui) {
    if (_kbhit() && !GameState::isGameOver && !GameState::isSleeping) {
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
                    GameState::GetGamePlayer()->EquipItem(ui.GetSelectionIndex());
                }
                catch(const std::out_of_range& e){
                    std::cerr <<'\n'<< e.what();
                }
                system("cls");
                ui.CheckSelection();
                ui.Render();
                break;
            case 'x':
                try{
                    GameState::GetGamePlayer()->SellItem(ui.GetSelectionIndex());
                }
                catch(const std::out_of_range& e){
                    std::cerr <<'\n'<< e.what();
                }
                system("cls");
                ui.CheckSelection();
                ui.Render();
                break;
            case 'i':
                return false;
        }
    }
    return true;
}

bool InputHandler::StatsUserInput(StatsUI& ui) {
    if (_kbhit() && !GameState::isGameOver && !GameState::isSleeping) {
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
                    GameState::GetGamePlayer()->AddStrength();
                else if (ui.GetOption(ui.GetSelectionIndex()) == "Mana")
                    GameState::GetGamePlayer()->AddMana();
                else if (ui.GetOption(ui.GetSelectionIndex()) == "Health Points")
                    GameState::GetGamePlayer()->AddHP();
                else if (ui.GetOption(ui.GetSelectionIndex()) == "Dexterity")
                    GameState::GetGamePlayer()->AddDexterity();
                ui.Render();
                break;
            case 'g':
                return false;
        }
    }
    return true;
}

void InputHandler::StartUserInput(StartMenuUI& ui, bool& OpenStartUI, bool& newGame, std::string& loadDir){
    if (_kbhit() && !GameState::isGameOver && !GameState::isSleeping) {
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
                        LoadGameUI loadUI("../Saves/");
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
                    case 2:{ //highscores
                        system("cls");
                        std::cout << "Highscores:\n-------------\n";
                        GameLoader::DisplayHighScores();
                        std::cout << "--------------------------\nPress any key to go back";
                        _getch();
                        system("cls");
                        ui.RenderArt();
                        ui.Render();
                        break;
                    }
                    case 3: //exit
                        GameState::EndGame();
                        OpenStartUI = false;
                        system("cls");
                        break;
                }
                break;
        }
    }
}

void InputHandler::LoadUserInput(LoadGameUI& ui, bool& OpenLoadGameUI, std::string& loadDir){
    if (_kbhit() && !GameState::isGameOver && !GameState::isSleeping) {
        int ch = _getch();
        switch (ch) {
            case 'w':
                ui.MoveSelection(0);
                break;
            case 's':
                ui.MoveSelection(1);
                break;
            case 'e':
                std::string dirName = "../Saves/" + ui.GetOption(ui.GetSelectionIndex());
                loadDir = dirName;
                OpenLoadGameUI = false;
                system("cls");
                break;
        }
    }
}

void InputHandler::RaceSelectUserInput(SelectionUI& ui, bool& OpenRaceSelectUI, Player::PlayerRace& race) {
    if (_kbhit() && !GameState::isGameOver && !GameState::isSleeping) {
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
                        race = Player::PlayerRace::Berserk;
                        break;
                    case 2:
                        race = Player::PlayerRace::Sorcerer;
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

void InputHandler::BattleUserInput(CombatEvents* event, BattleUI& ui, bool& playerIsDead, bool& monsterIsDead, bool& fled){
    if (_kbhit() && !GameState::isGameOver && !GameState::isSleeping) {
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