#include "Arena.h"
#include "Ball.h"

Arena::Arena(vector2d size): size_(size) {}

bool Arena::ballHitWallX(Ball ball) const {
    vector2d ball_position = ball.getPosition();
    float ball_radius = ball.getRadius();

    if (ball_position.x - ball_radius <= 0 || ball_position.x + ball_radius >= size_.x) return true;
    return false;
}

bool Arena::ballHitWallY(Ball ball) const {
    vector2d ball_position = ball.getPosition();
    float ball_radius = ball.getRadius();

    if (ball_position.y - ball_radius <= 0 || ball_position.y + ball_radius >= size_.y) return true;
    return false;
}

vector2d Arena::getSize() const {return size_;}