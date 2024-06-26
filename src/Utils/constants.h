#pragma once
#include <string>
#include <vector>

/**
 * @class Constants
 * @brief A class that contains various constants used in the project.
 */
class Constants {
public:
    // Chars
    static constexpr char BORDER_TOP = 219;  // 220
    static constexpr char BORDER_BOTTOM = 219;  // 223
    static constexpr char BORDER_SIDE = 219;
    static constexpr char WALL = 178;
    static constexpr char PATH = 176;
    static constexpr char EXIT = '#';
    static constexpr char MONSTER = 'M';
    static constexpr char TREASURE = 'T';
    static constexpr char PLAYER = '@';

    // Map Sizes
    static const std::vector<unsigned> STARTING_WIDTH;
    static const std::vector<unsigned> STARTING_HEIGHT;
    static const std::vector<unsigned> STARTING_TREASURE;
    static const std::vector<unsigned> STARTING_MONSTERS;
    static const std::vector<unsigned> CHUNK_SIZE;

    // Inventory
    static const unsigned INVENTORY_CAPACITY = 10;

    // Text
    static const std::string padding;

    // Colors
    static const unsigned DEFAULT_COLOR = 8;
    static const unsigned GREY = 8;
    static const unsigned BLUE = 3;
    static const unsigned GREEN = 10;
    static const unsigned YELLOW = 6;
    static const unsigned RED = 12;
    static const unsigned SELECTED_COLOR = 22;
};