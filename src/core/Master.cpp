#include "Master.h"
#include <algorithm>
#include <cmath>
#define PI 3.141592

// todo: move this mathematics nonsense into separate file
enum class GameState {Serving, Playing, GameOver};

//Ball bouncing off paddle requires more math, since we want to change angles at which the ball is moving (bounce ball perpendicularly when hitting paddle in the middle, bounce 89 deg or smth when hitting paddle corner)
vector2d calculateBounce(Ball &ball, Paddle &paddle) {
    float halfWidth = paddle.getSize().x / 2.0f;
    float paddleCenter = paddle.getPosition().x + halfWidth;

    //how far is the ball from the center of the paddle, cast on [-1,1]
    float offset = std::clamp((ball.getPosition().x - paddleCenter) / halfWidth, -1.0f, 1.0f);
    
    // can't believe there is no built-in function for this, 75deg is max angle of bounce
    // bonus: constexpr behaves a bit like DEFINE (compiles the value), while const just calculates it during runtime
    constexpr float maxAngleRad = 75.0f * (PI / 180.0f);
    float angle = offset * maxAngleRad;

    // no way, there is no function for changing to radians, but hypotenuse()? No problem!
    float speed = std::hypot(ball.getVelocity().x, ball.getVelocity().y);
    vector2d newVelocity = {speed * std::sin(angle), speed * std::cos(angle) * -1};  

    return newVelocity;
}

bool circleHitRectangle(vector2d circlePosition, float circleRadius, vector2d rectanglePosition, vector2d rectangleSize) {

    float closestX = std::clamp(circlePosition.x, rectanglePosition.x, rectanglePosition.x + rectangleSize.x);
    float closestY = std::clamp(circlePosition.y, rectanglePosition.y, rectanglePosition.y + rectangleSize.y);

    float dx = circlePosition.x - closestX;
    float dy = circlePosition.y - closestY;

    return (dx * dx + dy * dy) <= (circleRadius * circleRadius);
}

Master::Master(Ball ball, Arena arena, Player player, Paddle paddle, Brick brick): 
    ball_(ball),
    arena_(arena),
    player_(player),
    paddle_(paddle),
    brick_(brick)
    {}

void Master::handleWalls() {
    // check ball collision with arena walls
    // maybe call this 2 times, in case corner hit? 
    switch (arena_.checkWallHit(ball_))
    {
    case WallContact::Floor:
        //lose life, move game to serving
        break;

    case WallContact::Ceiling:
        ball_.bounceY();
        break;

    case WallContact::SideWall:
        ball_.bounceX();
        break;

    case WallContact::None:
        break;

    default:
        break;
    }
}

void Master::handlePaddleHit() {
    if (circleHitRectangle(ball_.getPosition(), ball_.getRadius(), paddle_.getPosition(), paddle_.getSize())) {
        vector2d newVelocity = calculateBounce(ball_, paddle_);
        ball_.setVelocity(newVelocity);
    }

}



void Master::tick(float dt) {
    // check game state first

    ball_.updatePosition(dt);

    handleWalls();
    handleWalls(); //second time in the special event of hitting a corner

    handlePaddleHit();

    handleBrickHit();
    handleBrickHit(); //again 






}

