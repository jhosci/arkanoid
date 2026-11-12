#include "Arena.h"
#include "Ball.h"

Arena::Arena(vector2d size): size_(size) {}

WallContact Arena::checkWallHit(Ball &ball) const {
    vector2d position = ball.getPosition();
    vector2d velocity = ball.getVelocity();
    float radius = ball.getRadius();

    bool touchesFloor   = position.y + radius >= size_.y && velocity.y > 0.f;
    bool touchesCeiling = position.y - radius <= 0.f     && velocity.y < 0.f;
    bool touchesLeft    = position.x - radius <= 0.f     && velocity.x < 0.f;
    bool touchesRight   = position.x + radius >= size_.x && velocity.x > 0.f;

    if (touchesFloor)   return WallContact::Floor;
    if (touchesCeiling) return WallContact::Ceiling;
    if (touchesLeft || touchesRight) return WallContact::SideWall;
    return WallContact::None;
}

vector2d Arena::getSize() const {return size_;}