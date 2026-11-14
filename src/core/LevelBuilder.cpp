#include "LevelBuilder.h"

std::vector<int> defaultLayout() {
    std::vector<int> layout(COLUMNS * ROWS, 1);
    return layout;
}

std::vector<std::unique_ptr<Brick>> buildLevel(const std::vector<int>& layout, vector2d arenaSize) {
    
    // bricks will take 50% of verictal space, leaving 10% free space on top and rest on the bottom
    const float brickWidth = arenaSize.x / COLUMNS;
    const float brickHeight = arenaSize.y / ROWS * 0.5f;
    const float topMargin = arenaSize.y * 0.1f;

    std::vector<std::unique_ptr<Brick>> bricks;

    for (int i = 0; i < layout.size(); i++) {
        if (layout[i] <= 0) continue;

        const float col = i % COLUMNS;
        const float row = i / COLUMNS;

        bricks.push_back(std::make_unique<Brick>(
            vector2d{col * brickWidth, topMargin + row * brickHeight},
            vector2d{brickWidth, brickHeight},
            layout[i],
            layout[i] * 10
            ));
    }
    return bricks;
}