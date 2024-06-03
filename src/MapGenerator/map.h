#pragma once
#include "vector"
#include "../Entities/player.h"
#include "renderer.h"
#include "../UI/selectionUI.h"
#include "../UI/battleUI.h"

/**
 * @class Map
 * @brief Represents the game map.
 *
 * The Map class handles the generation, rendering, and management of the game map,
 * including the player's position, obstacles, treasures, and monsters.
 */
class Map {
public:
    /**
     * @enum ObstacleDensity
     * @brief Defines the density of obstacles in the map.
     */
    enum ObstacleDensity {
        LABYRINTH = 1,       ///< High density, labyrinth-like.
        HIGH_DENSITY = 2,    ///< High obstacle density.
        MEDIUM_DENSITY = 3,  ///< Medium obstacle density.
        LOW_DENSITY = 4      ///< Low obstacle density.
    };

    /**
     * @brief Default constructor for Map.
     */
    Map();

    /**
     * @brief Constructs a Map with a given player.
     * @param player Pointer to the player.
     */
    Map(Player* player);

    /**
     * @brief Constructs a Map with specified dimensions and elements.
     * @param width Width of the map.
     * @param height Height of the map.
     * @param monsterCount Number of monsters in the map.
     * @param treasureCount Number of treasures in the map.
     * @param floor Current floor level.
     * @param player Pointer to the player.
     */
    Map(const unsigned width, const unsigned height, const unsigned monsterCount,
        const unsigned treasureCount, const unsigned floor, Player* player);

    /**
     * @brief Constructs a Map with specified dimensions, elements, and player position.
     * @param width Width of the map.
     * @param height Height of the map.
     * @param PlayerX X-coordinate of the player.
     * @param PlayerY Y-coordinate of the player.
     * @param monsterCount Number of monsters in the map.
     * @param treasureCount Number of treasures in the map.
     * @param floor Current floor level.
     * @param matrix 2D matrix representing the map layout.
     * @param player Pointer to the player.
     */
    Map(const unsigned width, const unsigned height, const unsigned PlayerX, const unsigned PlayerY, 
        const unsigned monsterCount, const unsigned treasureCount, const unsigned floor, 
        std::vector<std::vector<char>> matrix, Player* player);

    /**
     * @brief Copy constructor for Map.
     * @param other Another Map object to copy from.
     */
    Map(const Map& other);

    /**
     * @brief Move constructor for Map.
     * @param other Another Map object to move from.
     */
    Map(Map&& other) noexcept;

    /**
     * @brief Copy assignment operator for Map.
     * @param other Another Map object to assign from.
     * @return Reference to the assigned Map object.
     */
    Map& operator=(const Map& other);

    /**
     * @brief Move assignment operator for Map.
     * @param other Another Map object to move assign from.
     * @return Reference to the assigned Map object.
     */
    Map& operator=(Map&& other) noexcept;

    /**
     * @brief Destructor for Map.
     */
    ~Map();

    /**
     * @brief Initializes the map.
     */
    void Initialize();

    /**
     * @brief Creates a path starting from a given position.
     * @param i Row index.
     * @param j Column index.
     */
    void CreatePath(const int i, const int j);

    /**
     * @brief Counts visited neighbors of a cell.
     * @param i Row index.
     * @param j Column index.
     * @return Number of visited neighbors.
     */
    int countVisitedNeighbor(const int i, const int j) const;

    /**
     * @brief Generates the game map.
     */
    void GenerateMap();

    /**
     * @brief Creates treasures in the map.
     */
    void CreateTreasure();

    /**
     * @brief Creates monsters in the map.
     */
    void CreateMonsters();

    /**
     * @brief Places the player in the map.
     */
    void CreatePlayer();

    /**
     * @brief Creates an exit in the map.
     */
    void CreateExit();

    /**
     * @brief Renders all elements of the map.
     */
    void RenderAll() const;

    /**
     * @brief Renders player stats.
     */
    void RenderStats() const;

    /**
     * @brief Renders the entire map.
     */
    void RenderMap() const;

    /**
     * @brief Renders a chunk of the map.
     */
    void RenderChunk() const;

    /**
     * @brief Renders the player's position.
     */
    void RenderPosition();

    /**
     * @brief Renders a single tile.
     * @param c Character representing the tile.
     */
    void RenderTile(char c) const;

    /**
     * @brief Moves the player to a new position.
     * @param x New x-coordinate.
     * @param y New y-coordinate.
     */
    void MovePlayer(const int x, const int y);

    // Getters
    /**
     * @brief Gets the width of the map.
     * @return Width of the map.
     */
    unsigned GetWidth() const;

    /**
     * @brief Gets the height of the map.
     * @return Height of the map.
     */
    unsigned GetHeight() const;

    /**
     * @brief Gets the player's x-coordinate.
     * @return Player's x-coordinate.
     */
    unsigned GetPlayerX() const;

    /**
     * @brief Gets the player's y-coordinate.
     * @return Player's y-coordinate.
     */
    unsigned GetPlayerY() const;

    /**
     * @brief Gets the current floor level.
     * @return Current floor level.
     */
    unsigned GetFloor() const;

    /**
     * @brief Gets the player object.
     * @return Pointer to the player object.
     */
    Player* GetPlayer() const;

    /**
     * @brief Gets the map matrix.
     * @return 2D matrix representing the map layout.
     */
    std::vector<std::vector<char>> GetMatrix() const;

    /**
     * @brief Gets the number of monsters in the map.
     * @return Number of monsters in the map.
     */
    unsigned GetMonsterCount() const;

    /**
     * @brief Gets the number of treasures in the map.
     * @return Number of treasures in the map.
     */
    unsigned GetTreasureCount() const;

    /**
     * @brief Gets the renderer object.
     * @return Pointer to the renderer object.
     */
    Renderer* GetRenderer() const;

    // Setters
    /**
     * @brief Sets the player object.
     * @param player Pointer to the player object.
     */
    void SetPlayer(Player* player);

    /**
     * @brief Sets the width of the map.
     * @param width Width of the map.
     */
    void SetWidth(const unsigned width);

    /**
     * @brief Sets the height of the map.
     * @param height Height of the map.
     */
    void SetHeight(const unsigned height);

    /**
     * @brief Sets the player's x-coordinate.
     * @param playerX Player's x-coordinate.
     */
    void SetPlayerX(const unsigned playerX);

    /**
     * @brief Sets the player's y-coordinate.
     * @param playerY Player's y-coordinate.
     */
    void SetPlayerY(const unsigned playerY);

    /**
     * @brief Increases the floor level by one.
     */
    void IncreaseFloor();

private:
    Renderer* renderer;                     ///< Renderer object for rendering the map.
    unsigned width, height;                 ///< Dimensions of the map.
    unsigned playerX, playerY;              ///< Player's position coordinates.
    unsigned treasureCount, monsterCount;   ///< Number of treasures and monsters in the map.
    unsigned floor;                         ///< Current floor level.
    std::vector<std::vector<char>> matrix;  ///< 2D matrix representing the map layout.
    Player* player;                         ///< Pointer to the player object.
};