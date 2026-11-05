#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Brick.h"

/*
Module approx is because:
> 0.1 + 0.2
> 0.30000000000000004
*/

//To just see the syntax of catch2
TEST_CASE("Brick health behavior") {
    SECTION("Brick is destroyed after exactly hp hits") {

    
        Brick brick({0.f, 0.f}, {60.f, 20.f}, 3);

        CHECK_FALSE(brick.isDestroyed());
        brick.onHit();
        brick.onHit();
        CHECK_FALSE(brick.isDestroyed());   
        brick.onHit();
        CHECK(brick.isDestroyed());         
    }

    SECTION("Brick's hp does not go negative values") { // of course it will, I haven't written it yet
        Brick brick({0.f, 0.f}, {60.f, 20.f}, 1);

        brick.onHit();
        brick.onHit();

        CHECK(brick.isDestroyed());
        CHECK(brick.getHp() == 0);
    }
}