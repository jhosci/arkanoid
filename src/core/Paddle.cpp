#include "Paddle.h"
#include <algorithm>

Paddle::Paddle(vector2d position, vector2d size, float velocity, float minimumX, float maximumX): position_(position), size_(size), velocity_(velocity), minimumX_(minimumX), maximumX_(maximumX) {}


void Paddle::moveLeft(float dt) {
    position_.x = std::clamp(position_.x - velocity_ * dt, minimumX_, maximumX_-size_.x);

}

void Paddle::moveRight(float dt) {
    position_.x = std::clamp(position_.x + velocity_ * dt, minimumX_, maximumX_-size_.x);
}

vector2d Paddle::getPosition() const {return position_;}

vector2d Paddle::getSize() const {return size_;}

float Paddle::getVelocity() const {return velocity_;}