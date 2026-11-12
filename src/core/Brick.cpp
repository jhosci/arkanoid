#include "Brick.h"

Brick::Brick(vector2d position, vector2d size, int hp): position_(position), size_(size), hp_(hp) {}

void Brick::onHit() {hp_ -= 1;}

bool Brick::isDestroyed() const {return hp_ <= 0;}

vector2d Brick::getPosition() const {return position_;}

vector2d Brick::getSize() const {return size_;}

int Brick::getHp() const {return hp_;}