#pragma once
#include <iostream>
#include "selectionUI.h"
#include <filesystem>

static const COORD LOAD_GAME_SELECT_COORDINATES = {0, 0};

class LoadGameUI : public SelectionUI{
public:
    LoadGameUI(std::string path) : SelectionUI(LOAD_GAME_SELECT_COORDINATES){
        //read options from folder
        try {
            for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
                AddOption(entry.path().filename().string());
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

private:
};
 