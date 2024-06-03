#pragma once
#include <iostream>
#include "selectionUI.h"

static const COORD START_MENU_SELECT_COORDINATES = {1, 1};

/**
 * @class StartMenuUI
 * @brief Represents the user interface for the start menu.
 * 
 * The StartMenuUI class is responsible for rendering the start menu and managing its functionality.
 * It inherits from the SelectionUI class.
 */
class StartMenuUI : public SelectionUI{
public:
    /**
     * @brief Default constructor for StartMenuUI.
     */
    StartMenuUI();

    /**
     * @brief Copy constructor for StartMenuUI.
     * @param other The StartMenuUI object to be copied.
     */
    StartMenuUI(const StartMenuUI& other) = default;

    /**
     * @brief Default destructor for StartMenuUI.
     */
    ~StartMenuUI() = default;

    /**
     * @brief Renders the art for the start menu.
     */
    void RenderArt();

private:
    std::string art; /**< The art to be rendered on the start menu. */
};