#pragma once
#include <iostream>
#include "selectionUI.h"

static const COORD START_MENU_SELECT_COORDINATES = {1, 1};

class StartMenuUI : public SelectionUI{
public:
    //construction
    StartMenuUI();
    StartMenuUI(const StartMenuUI& other) = default;
    ~StartMenuUI() = default;

    void RenderArt();
private:
    std::string art;
};