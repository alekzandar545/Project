#pragma once
#include <iostream>
#include "selectionUI.h"

static const COORD START_MENU_SELECT_COORDINATES = {1, 1};

class StartMenuUI : public SelectionUI{
public:
    StartMenuUI();
    void RenderArt();
private:
    std::string art;
};