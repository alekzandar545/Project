#pragma once
#include  "../Entities/player.h"
#include <vector>
class Renderer{
private:
    unsigned CHUNK_COORDS[2] = {0,0};
public:
    //constructors
    Renderer() = default;
    Renderer(Renderer const &) = default;
	Renderer(Renderer &&) = default;
	Renderer &operator =(Renderer const &) = default;
	Renderer &operator =(Renderer &&) = default;
    //Rendering
    void RenderAll(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix, Player* player) const;
    void RenderStats(const unsigned heught, const unsigned width, Player* player) const;
    void RenderMap(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix) const;
    void RenderChunk(const unsigned height, const unsigned width, const std::vector<std::vector<char>> matrix) const;
    void RenderPosition(const unsigned height, const unsigned width, const unsigned playerX, const unsigned playerY, const std::vector<std::vector<char>> matrix);
    void RenderTile(char c) const;
    //setters
    void SetChunkX(const unsigned x);
    void SetChunkY(const unsigned y);
};