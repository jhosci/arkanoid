#include <catch2/catch_test_macros.hpp>
#include "Brick.h"

TEST_CASE("Brick tracks hit points and marks itself destroyed only when HP reaches zero") {
    SECTION("Brick with 3 HP survives two hits and is destroyed on the third") {
        Brick brick({100.f, 100.f}, {50.f, 20.f}, 3);

        brick.onHit();
        brick.onHit();
        REQUIRE_FALSE(brick.isDestroyed());

        brick.onHit();
        CHECK(brick.isDestroyed());
    }

    SECTION("Brick with 1 HP clamps HP at zero instead of going negative on extra hits") {
        Brick brick({100.f, 100.f}, {50.f, 20.f}, 1);

        brick.onHit();
        brick.onHit();

        CHECK(brick.getHp() == 0);
        CHECK(brick.isDestroyed());
    }
}