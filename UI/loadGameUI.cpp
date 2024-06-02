#include "LoadGameUI.h"

const COORD LoadGameUI::LOAD_GAME_SELECT_COORDINATES = {0,0};

LoadGameUI::LoadGameUI(std::string path) : SelectionUI(LOAD_GAME_SELECT_COORDINATES) {
    // Read options from folder
    try {
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
            AddOption(entry.path().filename().string());
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
