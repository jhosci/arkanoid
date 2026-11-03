#include "core.h"

//Also shouldn't be commenting in this file, in .h instead

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



Arena::Arena(vector2d size): size_(size) {}

bool Arena::ballHitWallX(Ball ball) const {
    vector2d ball_position = ball.getPosition();
    float ball_radius = ball.getRadius();

    // Left arena boundary is assumed 0; raising towards right
    if (ball_position.x - ball_radius <= 0 || ball_position.x + ball_radius >= size_.x) return true;
    return false;
}

bool Arena::ballHitWallY(Ball ball) const {
    vector2d ball_position = ball.getPosition();
    float ball_radius = ball.getRadius();

    // Upper arena boundary is assumed 0; raising towards bottom
    if (ball_position.y - ball_radius <= 0 || ball_position.y + ball_radius >= size_.y) return true;
    return false;
}

vector2d Arena::getSize() const {return size_;}



Brick::Brick(vector2d position, vector2d size, int hp): position_(position), size_(size), hp_(hp) {}

void Brick::onHit() {hp_ -= 1;}

vector2d Brick::getPosition() const {return position_;}

vector2d Brick::getSize() const {return size_;}

int Brick::getHp() const {return hp_;}

// METODY PALETKI
Paddle::Paddle(vector2d position, vector2d size, float velocity): position_(position), size_(size), velocity_(velocity) {}

void Paddle::moveLeft(float dt) {position_.x -= velocity_ * dt;}

void Paddle::moveRight(float dt) {position_.x += velocity_ * dt;}

// void Paddle::moveRight(float dt, float boundary) {
//     if ((position_.x + width_) >= boundary) {
//         position_.x = boundary - width_;
//     }
//     else {
//         position_.x += velocity_ * dt;
//     } 
// }

vector2d Paddle::getPosition() const {return position_;}

vector2d Paddle::getSize() const {return size_;}

float Paddle::getVelocity() const {return velocity_;}
