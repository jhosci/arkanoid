#include "Paddle.h"

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