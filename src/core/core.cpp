#include "core.h"

//Also shouldn't be commenting in this file, in .h instead

//METODY BAALA
Ball::Ball(vector2d startPos, vector2d startVel, float ballRadius) {
    //to read: initializer list?
    coordinates = startPos;
    velocity = startVel;
    radius = ballRadius;
}

void Ball::update_pos() {
    coordinates.x += velocity.x;
    coordinates.y += velocity.y; 
}

void Ball::bounceX() {
    velocity.x *= -1;
}
 
void Ball::bounceY() {
    velocity.y *= -1;
}

vector2d Ball::getPos() const {return coordinates;}

vector2d Ball::getVel() const {return velocity;}

//METODY ŚCIAN
Wall::Wall(vector2d bottomRight) {size = bottomRight;}

vector2d Wall::getSize() const {return size;}