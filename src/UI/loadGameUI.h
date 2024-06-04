#pragma once
#include <iostream>
#include <filesystem>
#include "selectionUI.h"

/**
 * @class LoadGameUI
 * @brief Represents the user interface for loading a game.
 * 
 * This class inherits from SelectionUI and provides functionality for loading a game.
 * It contains a constructor, a copy constructor, and a destructor.
 * The static constant LOAD_GAME_SELECT_COORDINATES represents the coordinates of the load game selection.
 */
class LoadGameUI : public SelectionUI {
public:
    /**
     * @brief Constructs a LoadGameUI object with the specified path.
     * @param path The path to the game file.
     */
    LoadGameUI(std::string path);

    /**
     * @brief Default copy constructor.
     * @param other The LoadGameUI object to be copied.
     */
    LoadGameUI(const LoadGameUI& other) = default;

    LoadGameUI& operator=(const LoadGameUI& other) = default;

    /**
     * @brief Default destructor.
     */
    ~LoadGameUI() override = default;

private:
    /**
     * @brief The coordinates of the load game selection.
     */
    static const COORD LOAD_GAME_SELECT_COORDINATES;
};