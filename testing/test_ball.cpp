#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Ball.h"

using Catch::Approx;

TEST_CASE("Ball updates position linearly based on velocity and delta time") { 

    Ball ball({0.f, 0.f}, {10.f, 5.f}, 10.f);
    ball.updatePosition(0.5f);

    CHECK(ball.getPosition().x == Approx(5.f));
    CHECK(ball.getPosition().y == Approx(2.5f));
}