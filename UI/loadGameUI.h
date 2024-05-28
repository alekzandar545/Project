#pragma once
#include <iostream>
#include "selectionUI.h"
#include <filesystem>

namespace fs = std::filesystem;

static const COORD LOAD_GAME_SELECT_COORDINATES = {0, 0};

class loadGameUI : public SelectionUI{
public:
    loadGameUI(std::string path) : SelectionUI(LOAD_GAME_SELECT_COORDINATES){
        //read options from folder
        try {
            for (const auto& entry : fs::directory_iterator(path)) {
                AddOption(entry.path().filename().string());
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

private:
};
 