#include "World.h"
#include "Geometry.h"
#include <algorithm>
#include <cmath>


//Ball bouncing off paddle requires more math, since we want to change angles at which the ball is moving (bounce ball perpendicularly when hitting paddle in the middle, bounce 75 deg or smth when hitting paddle corner)
vector2d calculateBounce(const Ball &ball, const Paddle &paddle) {
    float halfWidth = paddle.getSize().x / 2.0f;
    float paddleCenter = paddle.getPosition().x + halfWidth;

    //how far is the ball from the center of the paddle, cast on [-1,1]
    float offset = std::clamp((ball.getPosition().x - paddleCenter) / halfWidth, -1.0f, 1.0f);
    
    // can't believe there is no built-in function for this, 75deg is max angle of bounce
    // bonus: constexpr behaves a bit like DEFINE (compiles the value), while const just calculates it during runtime
    float maxAngleRad = radians(75.0f);
    float angle = offset * maxAngleRad;

    // no way, there is no function for changing to radians, but hypotenuse()? No problem!
    float speed = std::hypot(ball.getVelocity().x, ball.getVelocity().y);
    vector2d newVelocity = {speed * std::cos(angle), speed * std::sin(angle) * -1};

    return newVelocity;
}



World::World(Ball ball, Arena arena, Player player, Paddle paddle, std::vector<std::unique_ptr<Brick>> bricks): 
    ball_(ball),
    arena_(arena),
    player_(player),
    paddle_(paddle),
    bricks_(bricks)
    {}

void World::handleWalls() {
    // check ball collision with arena walls
    // maybe call this 2 times, in case corner hit? 
    switch (arena_.checkWallHit(ball_))
    {
    case WallContact::Floor:
        player_.loseLife();
        if (player_.gameOver()) {
            state_ = GameState::GameOver;
        } else {
            state_ = GameState::Serving;
        }
        break;

    case WallContact::Ceiling:
        ball_.bounceY();
        break;

    case WallContact::SideWall:
        ball_.bounceX();
        break;

    case WallContact::None:
        break;
    }
}

void World::handlePaddleHit() {
    if (ball_.getVelocity().y <= 0) return; //don't do if alr going up
    
    HitSide side = circleHitRectangle(ball_.getPosition(), ball_.getRadius(),paddle_.getPosition(), paddle_.getSize());

    if (side != HitSide::Top) return;

    ball_.setVelocity(calculateBounce(ball_, paddle_));
}

void World::createBallOnPaddle() {
    vector2d ballLocation = {paddle_.getPosition().x + paddle_.getSize().x / 2.0f,
        paddle_.getPosition().y - ball_.getRadius()};
    
    ball_ = Ball(ballLocation, {0.0f, 0.0f}, ball_.getRadius());
}

void World::movePaddleLeft(float dt) {paddle_.moveLeft(dt);}

void World::movePaddleRight(float dt) {paddle_.moveRight(dt);}

void World::launchBall() {
    if (state_ != GameState::Serving) return;

    float netVelocity = 10.0f;
    float angle = radians(90-15); //might later randomize it
    float velocityX = netVelocity  * std::cos(angle);
    float velocityY = netVelocity  * std::sin(angle);

    ball_.setVelocity({velocityX, velocityY});
    state_ = GameState::Playing;


}

void World::tick(float dt) {
    switch (state_)
    {
    case GameState::Serving:
        createBallOnPaddle();
        return;
    
    case GameState::GameOver:
       return;

    case GameState::Playing:
        break;
    }

    ball_.updatePosition(dt);

    handleWalls();
    if (state_ != GameState::Playing) return; 

    handlePaddleHit();

    handleBrickHit();

    removeDestroyedBricks();

    if (bricks_.empty()) state_ = GameState::Cleared;

}

