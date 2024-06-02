#pragma once
#include <string>
#include <vector>

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
};