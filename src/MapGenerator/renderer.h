#pragma once
#include  "../Entities/player.h"
#include <vector>
/**
 * @class Renderer
 * @brief The Renderer class is responsible for rendering the game map and player statistics on the console.
 */
class Renderer{
private:
    static std::vector<unsigned> CHUNK_COORDS;
public:
    //constructors
    Renderer();
    Renderer(const unsigned x, const unsigned y);
    Renderer(Renderer const &) = default;
	Renderer(Renderer &&) = default;
	Renderer &operator =(Renderer const &) = default;
	Renderer &operator =(Renderer &&) = default;
    //Rendering
    /**
     * @brief Clears the specified lines on the console.
     * @param startLine The starting line to clear.
     * @param endLine The ending line to clear.
     */
    static void ClearConsoleLines(int startLine, int endLine);
    /**
     * @brief Renders the entire game map and player position on the console.
     * @param height The height of the game map.
     * @param width The width of the game map.
     * @param matrix The game map matrix.
     * @param player The player object.
     */
    void RenderAll(const unsigned height, const unsigned width, const std::vector<std::vector<char>>& matrix, Player* player) const;
    /**
     * @brief Renders the player statistics on the console.
     * @param height The height of the game map.
     * @param width The width of the game map.
     * @param player The player object.
     */
    void RenderStats(const unsigned height, const unsigned width, Player* player) const;
    /**
     * @brief Renders the game map on the console.
     * @param height The height of the game map.
     * @param width The width of the game map.
     * @param matrix The game map matrix.
     */
    void RenderMap(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix) const;
    /**
     * @brief Renders a single chunk of the game map on the console.
     * @param height The height of the game map chunk.
     * @param width The width of the game map chunk.
     * @param matrix The game map chunk matrix.
     */
    void RenderChunk(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix) const;
    /**
     * @brief Renders the player position on the console.
     * @param height The height of the game map.
     * @param width The width of the game map.
     * @param playerX The X coordinate of the player.
     * @param playerY The Y coordinate of the player.
     * @param matrix The game map matrix.
     */
    void RenderPosition(const unsigned height, const unsigned width, const unsigned playerX, const unsigned playerY, const std::vector<std::vector<char>> matrix);
    /**
     * @brief Renders a single tile on the console.
     * @param c The character representing the tile.
     */
    void RenderTile(char c) const;
    //setters
    /**
     * @brief Sets the X coordinate of the game map chunk.
     * @param x The X coordinate to set.
     */
    void SetChunkX(const unsigned x);
    /**
     * @brief Sets the Y coordinate of the game map chunk.
     * @param y The Y coordinate to set.
     */
    void SetChunkY(const unsigned y);
    //getters
    /**
     * @brief Gets the X coordinate of the game map chunk.
     * @return The X coordinate of the game map chunk.
     */
    unsigned GetChunkX() const;
    /**
     * @brief Gets the Y coordinate of the game map chunk.
     * @return The Y coordinate of the game map chunk.
     */
    unsigned GetChunkY() const;
};