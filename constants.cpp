#include "constants.h"

// Initialize static members
bool Constants::isGameOver = false;

const std::vector<unsigned> Constants::STARTING_WIDTH = {10, 15};
const std::vector<unsigned> Constants::STARTING_HEIGHT = {10, 10};
const std::vector<unsigned> Constants::STARTING_TREASURE = {2, 2};
const std::vector<unsigned> Constants::STARTING_MONSTERS = {2, 3};
const std::vector<unsigned> Constants::CHUNK_SIZE = {30, 10};

const std::string Constants::padding = "                                                         ";