// CZY DAMY RADĘ?
// TAK, DAMY RADĘ!

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "LevelBuilder.h"

using Catch::Approx;

TEST_CASE("LevelBuilder constructs brick grid with calculated positions, HP, and scores") {
    const vector2d arenaSize{800.f, 600.f};

    SECTION("Bricks tile the grid: a row spans the arena width and each cell follows the previous one") {
        std::vector<int> layout(COLUMNS * ROWS, 0);
        layout[0] = 1;
        layout[2 * COLUMNS + 1] = 1;

        const auto bricks = buildLevel(layout, arenaSize);
        REQUIRE(bricks.size() == 2);

        const vector2d size = bricks[0]->getSize();
        const vector2d first = bricks[0]->getPosition();
        const vector2d second = bricks[1]->getPosition();

        CHECK(size.x * COLUMNS == Approx(arenaSize.x));
        CHECK(size.y * ROWS == Approx(arenaSize.y * 0.5f));
        CHECK(first.x == Approx(0.f));
        CHECK(first.y == Approx(arenaSize.y * 0.1f));
        CHECK(second.x == Approx(first.x + size.x));
        CHECK(second.y == Approx(first.y + 2.f * size.y));       
    }

    SECTION("Returns an empty vector when all layout cells are zero") {
        std::vector<int> layout(COLUMNS * ROWS, 0);
        CHECK(buildLevel(layout, arenaSize).empty());
    }

    SECTION("defaultLayout creates a full COLUMS*ROWS grid of 1-HP bricks") {
        auto layout = defaultLayout();
        REQUIRE(layout.size() == COLUMNS * ROWS);
        for (int cell : layout) {
            CHECK(cell == 1);
        }
    }
}