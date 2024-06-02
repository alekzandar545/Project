#include "GameLoader.h"
#include "constants.h"
#include <iostream>
#include <algorithm>

bool GameLoader::LoadGame(Player& player, Map& map, const std::string& saveFile) {
    std::ifstream reader(saveFile);
    if (!reader) {
        throw std::runtime_error("Failed to open save file: " + saveFile);
    }

    // Load player data
    if (!LoadPlayer(reader, player)) {
        std::cerr << "Failed to load player data." << std::endl;
        return false;
    }

    // Load map data
    if (!LoadMap(reader, map, &player)) {
        std::cerr << "Failed to load map data." << std::endl;
        return false;
    }

    reader.close();
    return true;
}

void GameLoader::LoadHighScores(std::vector<Player>& characters, const std::string& path) {
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
        Player player;
        std::string saveFile = path + '/' + entry.path().filename().string();
        std::ifstream reader(saveFile);
        if (!reader) {
            throw std::runtime_error("Failed to open save file: " + saveFile);
        }
        LoadPlayer(reader, player);
        characters.push_back(player);
    }
}

void GameLoader::DisplayHighScores(const std::string& path) {
    std::vector<Player> characters;
    LoadHighScores(characters, path);
    // Sort players by gold count in descending order
    std::sort(characters.begin(), characters.end(), [](const Player& a, const Player& b) {
        return a.GetGold() > b.GetGold();
    });
    // Display the top 10 players
    std::cout << "Top 10 High Scores:\n";
    for (size_t i = 0; i < characters.size() && i < 10; ++i) {
        std::cout << i + 1 << ". " << characters[i].GetName() << " - " << characters[i].GetGold() << " gold\n";
    }
}

bool GameLoader::LoadPlayer(std::ifstream& reader, Player& player) {
    std::string name;
    unsigned str;
    unsigned mana;
    unsigned maxHP;
    int HP;
    unsigned armor;
    unsigned dexterity;
    unsigned statPoints;
    unsigned level;
    unsigned xp;
    unsigned requiredXp;
    unsigned gold;
    unsigned inventorySize;
    std::vector<Item> inventory;
    Item weapon;
    Item spell;
    Item armorPiece;
    reader >> name >> str >> mana >> maxHP >> HP >> armor >> dexterity >> statPoints >> level >> xp 
           >> requiredXp >> gold >> inventorySize;
    if (inventorySize > 10)
        throw std::out_of_range("Trying to inject too many items!");

    // now inject the items from the inventory
    for (size_t i = 0; i < inventorySize; i++) {
        Item item;
        LoadItem(reader, item);
        inventory.push_back(item);
    }

    // inject equipped items
    LoadItem(reader, weapon);
    LoadItem(reader, spell);
    LoadItem(reader, armorPiece);
    if (reader.fail()) {
        throw std::runtime_error("Failed to load player data.");
    }

    // need to reformat the name
    std::replace(name.begin(), name.end(), '_', ' ');
    player = Player(name, str, mana, maxHP, HP, armor, dexterity, statPoints, level,
                    xp, requiredXp, gold, inventory, weapon, spell, armorPiece);
    return true;
}

bool GameLoader::LoadItem(std::ifstream& reader, Item& item) {
    int type;
    std::string name;
    unsigned power;
    reader >> type >> name >> power;
    if (reader.fail()) {
        throw std::runtime_error("Failed to load item data.");
    }

    // need to reformat the name
    std::replace(name.begin(), name.end(), '_', ' ');
    item = Item(name, static_cast<Item::ItemType>(type), power);
    return true;
}

bool GameLoader::LoadMap(std::ifstream& reader, Map& map, Player* player) {
    unsigned width, height, playerX, playerY, chunkX, 
             chunkY, monsterCount, treasureCount, floor;
    reader >> width >> height >> playerX >> playerY >> chunkX >>
              chunkY >> monsterCount >> treasureCount >> floor;
    std::vector<std::vector<char>> matrix(height, std::vector<char>(width));

    // Read the matrix from the file
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            unsigned char ch;
            reader >> ch;
            if (ch == '%')
                ch = Constants::WALL;
            if (ch == '.')
                ch = Constants::PATH;
            if (reader.fail()) {
                throw std::runtime_error("Failed to read matrix data.");
            }
            matrix[y][x] = ch;
        }
    }
    if (reader.fail()) {
        throw std::runtime_error("Failed to load map data.");
    }

    map = Map(width, height, playerX, playerY, monsterCount,
              treasureCount, floor, matrix, player);
    map.renderer->SetChunkX(chunkX);
    map.renderer->SetChunkY(chunkY);
    return true;
}
