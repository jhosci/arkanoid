#include <catch2/catch_test_macros.hpp>
#include "Arena.h"
#include "Ball.h"

TEST_CASE("Arena detects wall contacts only when ball touches a boundary while moving toward it") {
    Arena arena({800.f, 600.f});
    const float radius = 10.f;

    SECTION("Returns None when ball is in the middle of the arena") {
        CHECK(arena.checkWallHit(Ball({400.f, 300.f}, {100.f, 100.f}, radius)) == WallContact::None);
    }

    SECTION("Detects Left and Right SideWall contacts at exact radius distance") {
        CHECK(arena.checkWallHit(Ball({10.f, 300.f}, {-100.f, 0.f}, radius)) == WallContact::SideWall);
        CHECK(arena.checkWallHit(Ball({11.f, 300.f}, {-100.f, 0.f}, radius)) == WallContact::None);

        CHECK(arena.checkWallHit(Ball({790.f, 300.f}, {100.f, 0.f}, radius)) == WallContact::SideWall);
        CHECK(arena.checkWallHit(Ball({789.f, 300.f}, {100.f, 0.f}, radius)) == WallContact::None);
    }

    SECTION("Detects Ceiling and Floor contacts at exact radius distance") {
        CHECK(arena.checkWallHit(Ball({400.f, 10.f}, {0.f, -100.f}, radius)) == WallContact::Ceiling);
        CHECK(arena.checkWallHit(Ball({400.f, 11.f}, {0.f, -100.f}, radius)) == WallContact::None);

        CHECK(arena.checkWallHit(Ball({400.f, 590.f}, {0.f, 100.f}, radius)) == WallContact::Floor);
        CHECK(arena.checkWallHit(Ball({400.f, 589.f}, {0.f, 100.f}, radius)) == WallContact::None);
    }

    SECTION("Ignores wall overlap when ball is already moving away from the wall") {
        CHECK(arena.checkWallHit(Ball({5.f, 300.f}, {100.f, 0.f}, radius)) == WallContact::None);
        CHECK(arena.checkWallHit(Ball({795.f, 300.f}, {-100.f, 0.f}, radius)) == WallContact::None);
        CHECK(arena.checkWallHit(Ball({400.f, 5.f}, {0.f, 100.f}, radius)) == WallContact::None);
        CHECK(arena.checkWallHit(Ball({400.f, 595.f}, {0.f, -100.f}, radius)) == WallContact::None);
    }

    SECTION("Prioritizes Floor and Ceiling over SideWall on simultaneoueus corner contacts") {
        CHECK(arena.checkWallHit(Ball({10.f, 590.f}, {-100.f, 100.f}, radius)) == WallContact::Floor);
        CHECK(arena.checkWallHit(Ball({10.f, 10.f}, {-100.f, -100.f}, radius)) == WallContact::Ceiling);
    }
}