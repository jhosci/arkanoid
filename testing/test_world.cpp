#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <cmath>
#include <memory>
#include <numbers>
#include <utility>
#include <vector>
#include "World.h"

using Catch::Approx;

// Shared setup for every test below:
// arena 800x600, ball radius 10
// paddle at (350, 550), size 100x20

// To shorten my misery (typing tooo much) - using namespace which is a set of definitions accessible globally BUT only in scope of this file
namespace {
using BrickList = std::vector<std::unique_ptr<Brick>>;

// A brick parked in a far corner, bc tickmachinae flags a level with no bricks as cleared
BrickList parkedBrick() {
    BrickList bricks;
    bricks.push_back(std::make_unique<Brick>(vector2d{700.f, 60.f}, vector2d{50.f, 20.f}, 1));
    return bricks;
}

World makeWorld(Ball ball, GameState state, BrickList bricks = parkedBrick(), Player player = Player()) {
    return World(ball, Arena({800.f, 600.f}), player,
                 Paddle({350.f, 550.f}, {100.f, 20.f}, 300.f, 0.f, 800.f),
                 std::move(bricks), state);
}

World makeServingWorld() {
    return makeWorld(Ball({0.f, 0.f}, {0.f, 0.f}, 10.f), GameState::Serving);
}

World makePlayingWorld(Ball ball, BrickList bricks = parkedBrick(), Player player = Player()) {
    return makeWorld(ball, GameState::Playing, std::move(bricks), player);
}
}

TEST_CASE("A new world starts in Serving with a stationary ball centered on the paddle") {
    World world = makeServingWorld();

    CHECK(world.state() == GameState::Serving);
    CHECK(world.ball().getPosition().x == Approx(400.f));
    CHECK(world.ball().getPosition().y == Approx(540.f));
    CHECK(world.ball().getVelocity().x == Approx(0.f));
    CHECK(world.ball().getVelocity().y == Approx(0.f));
}

TEST_CASE("Moving the paddle during Serving moves the ball along with it") {
    World world = makeServingWorld();

    world.movePaddleRight(0.1f);
    world.tick(0.1f);

    CHECK(world.paddle().getPosition().x == Approx(380.f));
    CHECK(world.ball().getPosition().x == Approx(430.f));
}

TEST_CASE("Launching the ball enters Playing with an upward-right velocity") {
    World world = makeServingWorld();

    world.launchBall();

    CHECK(world.state() == GameState::Playing);
    CHECK(world.ball().getVelocity().y < 0.f);
    CHECK(world.ball().getVelocity().x > 0.f);
}

TEST_CASE("launchBall is ignored unless the world is Serving") {
    World world = makePlayingWorld(Ball({400.f, 300.f}, {-50.f, 80.f}, 10.f));

    world.launchBall();

    CHECK(world.ball().getVelocity().x == Approx(-50.f));
    CHECK(world.ball().getVelocity().y == Approx(80.f));
}

TEST_CASE("A Playing tick advances the ball by velocity * dt") {
    World world = makePlayingWorld(Ball({400.f, 300.f}, {100.f, 50.f}, 10.f));

    world.tick(0.1f);

    CHECK(world.ball().getPosition().x == Approx(410.f));
    CHECK(world.ball().getPosition().y == Approx(305.f));
}

TEST_CASE("Ticking in GameOver changes nothing") {
    World world = makeWorld(Ball({400.f, 300.f}, {100.f, 100.f}, 10.f), GameState::GameOver);

    world.tick(1.0f);

    CHECK(world.ball().getPosition().x == Approx(400.f));
    CHECK(world.ball().getPosition().y == Approx(300.f));
    CHECK(world.state() == GameState::GameOver);
}

TEST_CASE("A ball hitting the ceiling bounces back down") {
    World world = makePlayingWorld(Ball({400.f, 10.f}, {0.f, -100.f}, 10.f));

    world.tick(0.f);

    CHECK(world.ball().getVelocity().x == Approx(0.f));
    CHECK(world.ball().getVelocity().y == Approx(100.f));
}

TEST_CASE("A ball hitting a side wall reverses its horizontal velocity") {
    World world = makePlayingWorld(Ball({10.f, 300.f}, {-100.f, 50.f}, 10.f));

    world.tick(0.f);

    CHECK(world.ball().getVelocity().x == Approx(100.f));
    CHECK(world.ball().getVelocity().y == Approx(50.f));
}

TEST_CASE("Losing the ball with lives remaining costs a life and puts it back on the paddle") {
    World world = makePlayingWorld(Ball({400.f, 590.f}, {0.f, 100.f}, 10.f), parkedBrick(), Player(3));

    world.tick(0.f);

    CHECK(world.player().getLives() == 2);
    CHECK(world.state() == GameState::Serving);
    CHECK(world.ball().getPosition().x == Approx(400.f));
    CHECK(world.ball().getPosition().y == Approx(540.f));
    CHECK(world.ball().getVelocity().x == Approx(0.f));
    CHECK(world.ball().getVelocity().y == Approx(0.f));
}

TEST_CASE("Losing the ball on the last life transitions the world to GameOver") {
    World world = makePlayingWorld(Ball({400.f, 590.f}, {0.f, 100.f}, 10.f), parkedBrick(), Player(1));

    world.tick(0.f);

    CHECK(world.player().getLives() == 0);
    CHECK(world.state() == GameState::GameOver);
}

TEST_CASE("A ball hitting the center of the paddle bounces straight up") {
    World world = makePlayingWorld(Ball({400.f, 545.f}, {0.f, 100.f}, 10.f));

    world.tick(0.f);

    CHECK(world.ball().getVelocity().x == Approx(0.f).margin(1e-4f));
    CHECK(world.ball().getVelocity().y == Approx(-100.f));
}

TEST_CASE("A ball hitting the right edge of the paddle bounces at 75 degrees and keeps its speed") {
    World world = makePlayingWorld(Ball({450.f, 545.f}, {0.f, 100.f}, 10.f));

    world.tick(0.f);

    const vector2d v = world.ball().getVelocity();
    CHECK(std::hypot(v.x, v.y) == Approx(100.f));
    CHECK(v.x > 0.f);
    CHECK(v.y < 0.f);

    const float angleFromVerticalDeg = std::atan2(v.x, -v.y) * 180.f / std::numbers::pi_v<float>;
    CHECK(angleFromVerticalDeg == Approx(75.f).margin(0.01f));
}

TEST_CASE("A ball moving upward through the paddle is not deflected") {
    World world = makePlayingWorld(Ball({420.f, 545.f}, {0.f, -100.f}, 10.f));

    world.tick(0.f);

    CHECK(world.ball().getVelocity().x == Approx(0.f));
    CHECK(world.ball().getVelocity().y == Approx(-100.f));
}

TEST_CASE("A ball touching the side of the paddle instead of its top face is ignored") {
    World world = makePlayingWorld(Ball({345.f, 560.f}, {50.f, 100.f}, 10.f));

    world.tick(0.f);

    CHECK(world.ball().getVelocity().x == Approx(50.f));
    CHECK(world.ball().getVelocity().y == Approx(100.f));
}

TEST_CASE("A 1-hp brick hit from below is destroyed, scores, and keeps Playing if another brick remains") {
    BrickList bricks = parkedBrick();
    bricks.push_back(std::make_unique<Brick>(vector2d{100.f, 100.f}, vector2d{50.f, 20.f}, 1));
    World world = makePlayingWorld(Ball({125.f, 125.f}, {0.f, -100.f}, 10.f), std::move(bricks));

    world.tick(0.f);

    CHECK(world.ball().getVelocity().y == Approx(100.f));
    CHECK(world.bricks().size() == 1);           
    CHECK(world.player().getScore() == 10);      
    CHECK(world.state() == GameState::Playing);
}

TEST_CASE("A ball hitting the side of a brick reverses its horizontal velocity") {
    BrickList bricks;
    bricks.push_back(std::make_unique<Brick>(vector2d{100.f, 100.f}, vector2d{50.f, 20.f}, 2));
    World world = makePlayingWorld(Ball({95.f, 110.f}, {100.f, 0.f}, 10.f), std::move(bricks));

    world.tick(0.f);

    CHECK(world.ball().getVelocity().x == Approx(-100.f));
    CHECK(world.ball().getVelocity().y == Approx(0.f));
}

TEST_CASE("A ball overlapping a brick while moving away does not damage it") {
    BrickList bricks;
    bricks.push_back(std::make_unique<Brick>(vector2d{100.f, 100.f}, vector2d{50.f, 20.f}, 1));
    World world = makePlayingWorld(Ball({125.f, 125.f}, {0.f, 100.f}, 10.f), std::move(bricks));

    world.tick(0.f);

    REQUIRE(world.bricks().size() == 1);
    CHECK(world.bricks()[0]->getHp() == 1);
}

TEST_CASE("A 2-hp brick survives its first hit without scoring and is not hit again by a second tick") {
    BrickList bricks;
    bricks.push_back(std::make_unique<Brick>(vector2d{100.f, 100.f}, vector2d{50.f, 20.f}, 2, 20));
    World world = makePlayingWorld(Ball({125.f, 125.f}, {0.f, -100.f}, 10.f), std::move(bricks));

    world.tick(0.f);
    REQUIRE(world.bricks().size() == 1);
    CHECK(world.bricks()[0]->getHp() == 1);
    CHECK(world.player().getScore() == 0);

    world.tick(0.f);   
    CHECK(world.bricks()[0]->getHp() == 1);
}

TEST_CASE("A ball hitting the seam between two adjacent bricks damages only one of them") {
    BrickList bricks;
    bricks.push_back(std::make_unique<Brick>(vector2d{100.f, 100.f}, vector2d{50.f, 20.f}, 2));
    bricks.push_back(std::make_unique<Brick>(vector2d{150.f, 100.f}, vector2d{50.f, 20.f}, 2));
    World world = makePlayingWorld(Ball({150.f, 125.f}, {0.f, -100.f}, 10.f), std::move(bricks));

    world.tick(0.f);

    REQUIRE(world.bricks().size() == 2);
    CHECK((world.bricks()[0]->getHp() + world.bricks()[1]->getHp()) == 3);
}

TEST_CASE("Destroying the final brick clears the level and stops further ball movement") {
    BrickList bricks;
    bricks.push_back(std::make_unique<Brick>(vector2d{100.f, 100.f}, vector2d{50.f, 20.f}, 1));
    World world = makePlayingWorld(Ball({125.f, 125.f}, {0.f, -100.f}, 10.f), std::move(bricks));

    world.tick(0.f);
    CHECK(world.state() == GameState::Cleared);

    const vector2d positionAtClear = world.ball().getPosition();
    world.tick(1.0f);
    CHECK(world.ball().getPosition().x == Approx(positionAtClear.x));
    CHECK(world.ball().getPosition().y == Approx(positionAtClear.y));
}