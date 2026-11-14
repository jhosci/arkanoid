// there will be 24x16 bricks grid to create levels
// the most basic playable level will be just a grid full of std bricks
// soon™ there will be drawing levels from file input
#pragma once
#include "Brick.h"
#include <vector>
#include <memory>

constexpr int COLUMNS = 24;
constexpr int ROWS = 16;


// Levels are a kColumns x kRows grid, stored row by row in a flat vector.
// Each cell is the hit points of the brick in it; 0 means no brick.
std::vector<int> defaultLayout();
std::vector<std::unique_ptr<Brick>> buildLevel(const std::vector<int>& layout, vector2d arenaSize);

