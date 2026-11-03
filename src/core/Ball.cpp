#include "Ball.h"

Ball::Ball(vector2d position, vector2d velocity, float radius): position_(position), velocity_(velocity), radius_(radius) {}

void Ball::updatePosition(float dt) {
    position_.x += velocity_.x * dt;
    position_.y += velocity_.y * dt; 
}

void Ball::bounceX() {
    velocity_.x *= -1;
}
 
void Ball::bounceY() {
    velocity_.y *= -1;
}

vector2d Ball::getPosition() const {return position_;}

vector2d Ball::getVelocity() const {return velocity_;}

float Ball::getRadius() const {return radius_;}