#pragma once
#include <string>

//gameState
extern bool isGameOver; 
static void EndGame(){
    isGameOver=true;
}
//chars
static const char BORDER_TOP = 219;//220
static const char BORDER_BOTTOM = 219;//223
static const char BORDER_SIDE = 219;
static const char WALL = 178;
static const char PATH = 176;
static const char EXIT = '#';
static const char MONSTER = 'M';
static const char TREASURE = 'T';
static const char PLAYER = '@';
//mapsizes
static const unsigned STARTING_WIDTH[] = {10,15};
static const unsigned STARTING_HEIGHT[] = {10,10};
static const unsigned STARTING_TREASURE[] = {2,2};
static const unsigned STARTING_MONSTERS[] = {2,3};
static const unsigned CHUNK_SIZE[] = {30,10};
//text
static const std::string padding = "                                                         ";
//colors