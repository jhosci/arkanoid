#include "core.h"

//Also shouldn't be commenting in this file, in .h instead

//METODY BAALA
Ball::Ball(vector2d startPos, vector2d startVel, float ballRadius) {
    //to read: initializer list?
    coordinates_ = startPos;
    velocity_ = startVel;
    radius_ = ballRadius;
}

void Ball::update_pos() {
    coordinates_.x += velocity_.x;
    coordinates_.y += velocity_.y; 
}

void Ball::bounceX() {
    velocity_.x *= -1;
}
 
void Ball::bounceY() {
    velocity_.y *= -1;
}

vector2d Ball::getPos() const {return coordinates_;}

vector2d Ball::getVel() const {return velocity_;}

//METODY ŚCIAN
Wall::Wall(vector2d bottomRight) {size_ = bottomRight;}

vector2d Wall::getSize() const {return size_;}

// METODY CEGIEL
Brick::Brick(vector2d coordinates, int hp) {
    coordinates_ = coordinates;
    hp_ = hp;
};

vector2d Brick::getPos() const {return coordinates_;}
int Brick::getHp() const {return hp_;}
