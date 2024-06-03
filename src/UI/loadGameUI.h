#pragma once
#include <iostream>
#include <filesystem>
#include "selectionUI.h"

class LoadGameUI : public SelectionUI {
public:
    LoadGameUI(std::string path);
    LoadGameUI(const LoadGameUI& other) = default;
    ~LoadGameUI() = default;
private:
    static const COORD LOAD_GAME_SELECT_COORDINATES;
};