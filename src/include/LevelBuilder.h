// the most basic playable level will be just a grid full of std bricks
// soon™ there will be drawing levels from file input
#pragma once
#include "Brick.h"
#include <vector>
#include <memory>

constexpr int COLUMNS = 12;
constexpr int ROWS = 8;


// Levels are a COLUMNS * ROWS grid, stored row by row in a flat vector.
// Each cell is the hit points of the brick in it; 0 means no brick.
// deprecated, temporary solution to fill the layout with 1hp bricks
std::vector<int> defaultLayout();
// BuildLvel builds the list of pointers to bricks, the datatype game uses for bricks
std::vector<std::unique_ptr<Brick>> buildLevel(const std::vector<int>& layout, vector2d arenaSize);
// CreateLevel takes lvl number & arena size, creates a list of int's (rows of bricks of x) and calls BuildLevel to make a list of bricks off of it
// Now just hardcoded loop; laterwill draw layouts from filesbased on lvl number
std::vector<std::unique_ptr<Brick>> createLevel(int level, vector2d arenaSize);

