#pragma once
#include "map.h"
class Renderer{
    private:
        static Map* map;
        static Renderer* instancePtr;
        static unsigned floor;
    public:
    //constructors
    Renderer() = default;
    Renderer(Renderer const &) = delete;
	Renderer(Renderer &&) = delete;
	Renderer &operator =(Renderer const &) = delete;
	Renderer &operator =(Renderer &&) = delete;
    //singleton design
	static Renderer* GetInstance(Map* map);
    //Rendering
    void RenderMap() const;
    void RenderChunk(const unsigned* ChunkCoords) const;
    void RenderPosition() const;
    void RenderTile(char c) const;
};