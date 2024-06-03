#pragma once
#include  "../Entities/player.h"
#include <vector>
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
    static void ClearConsoleLines(int startLine, int endLine);
    void RenderAll(const unsigned height, const unsigned width, const std::vector<std::vector<char>>& matrix, Player* player) const;
    void RenderStats(const unsigned heught, const unsigned width, Player* player) const;
    void RenderMap(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix) const;
    void RenderChunk(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix) const;
    void RenderPosition(const unsigned height, const unsigned width, const unsigned playerX, const unsigned playerY, const std::vector<std::vector<char>> matrix);
    void RenderTile(char c) const;
    //setters
    void SetChunkX(const unsigned x);
    void SetChunkY(const unsigned y);
    //getters
    unsigned GetChunkX() const;
    unsigned GetChunkY() const;
};