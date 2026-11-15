#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Paddle.h"

using Catch::Approx;

TEST_CASE("Paddle moves horizontally by speed * dt and clamps within arena bounds") {
    SECTION("Paddle shifts right and left proportionally to elapsed time") {
        Paddle paddle({350.f, 550.f}, {100.f, 20.f}, 300.f, 0.f, 800.f);

        paddle.moveRight(0.1f);
        CHECK(paddle.getPosition().x == Approx(380.f));

        paddle.moveLeft(0.1f);
        CHECK(paddle.getPosition().x == Approx(350.f));

        paddle.moveLeft(0.1f);
        CHECK(paddle.getPosition().x == Approx(320.f));
    }

    SECTION("Paddle stops at the left boundary without going negative") {
        Paddle paddle({10.f, 550.f}, {100.f, 20.f}, 300.f, 0.f, 800.f);
        paddle.moveLeft(10.f);

        CHECK(paddle.getPosition().x == Approx(0.f));
    }

    SECTION("Paddle stops so its right edge aligns with the arena width") {
        Paddle paddle({690.f, 550.f}, {100.f, 20.f}, 300.f, 0.f, 800.f);
        paddle.moveRight(10.f);

        CHECK(paddle.getPosition().x == Approx(700.f));
    }
}