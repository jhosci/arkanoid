// CZY DAMY RADĘ?
// TAK, DAMY RADĘ!

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "LevelBuilder.h"

using Catch::Approx;

TEST_CASE("LevelBuilder constructs brick grid with calculated positions, HP, and scores") {
    const vector2d arenaSize{800.f, 600.f};

    SECTION("Places bricks only for non-zero cells with coordinates and score scaled by HP") {
        std::vector<int> layout(COLUMNS * ROWS, 0);
        layout[0] = 1;
        layout[COLUMNS + 1] = 3;

        auto bricks = buildLevel(layout, arenaSize);
        REQUIRE(bricks.size() == 2);

        CHECK(bricks[0]->getPosition().x == Approx(0.f));
        CHECK(bricks[0]->getPosition().y == Approx(60.f));
        CHECK(bricks[0]->getHp() == 1);
        CHECK(bricks[0]->getScore() == 10);

        CHECK(bricks[1]->getPosition().x == Approx(800.f / 24.f));
        CHECK(bricks[1]->getPosition().y == Approx(78.75f));
        CHECK(bricks[1]->getHp() == 3);
        CHECK(bricks[1]->getScore() == 30);
    }

    SECTION("Returns an empty vector when all layout cells are zero") {
        std::vector<int> layout(COLUMNS * ROWS, 0);
        CHECK(buildLevel(layout, arenaSize).empty());
    }

    SECTION("defaultLayout creates a full 24x16 grid of 1-HP bricks") {
        auto layout = defaultLayout();
        REQUIRE(layout.size() == COLUMNS * ROWS);
        for (int cell : layout) {
            CHECK(cell == 1);
        }
    }
}