#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <numbers>
#include "Geometry.h"

using Catch::Approx;

TEST_CASE("circleHitRectangle identifies which rectangle face the circle collides with") {
    const vector2d brickPos{100.0f, 100.0f};
    const vector2d brickSize{50.0f, 20.0f};
    const float radius = 10.0f;

    SECTION("Detects collisions on each of the four faces and returns None when separated") {
        CHECK(circleHitRectangle({95.0f, 110.0f}, radius, brickPos, brickSize) == HitSide::Left);
        CHECK(circleHitRectangle({155.0f, 110.0f}, radius, brickPos, brickSize) == HitSide::Right);
        CHECK(circleHitRectangle({125.0f, 95.0f}, radius, brickPos, brickSize) == HitSide::Top);
        CHECK(circleHitRectangle({125.0f, 125.0f}, radius, brickPos, brickSize) == HitSide::Bottom);
        CHECK(circleHitRectangle({125.0f, 140.0f}, radius, brickPos, brickSize) == HitSide::None);
    }

    SECTION("Counts exact edge contact as a hit and one pixel short as a miss") {
        CHECK(circleHitRectangle({90.0f, 110.0f}, radius, brickPos, brickSize) == HitSide::Left);
        CHECK(circleHitRectangle({89.0f, 110.0f}, radius, brickPos, brickSize) == HitSide::None);
    }

    SECTION("Resolves corner overlaps by dominant axis and breaks exact ties in favor of Top") {
        CHECK(circleHitRectangle({95.0f, 97.0f}, radius, brickPos, brickSize) == HitSide::Left);
        CHECK(circleHitRectangle({97.0f, 95.0f}, radius, brickPos, brickSize) == HitSide::Top);
        CHECK(circleHitRectangle({95.0f, 95.0f}, radius, brickPos, brickSize) == HitSide::Top);
    }
}

TEST_CASE("Radians converts degrees to radians accurately") {
    CHECK(radians(180.0f) == Approx(std::numbers::pi));
}