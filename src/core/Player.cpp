#include "Player.h"

Player::Player(int lives, int score, int level): lives_(lives), score_(score), level_(level) {}

void Player::nextLevel() {level_ += 1;}

bool Player::gameOver() const {return lives_ <= 0;}

void Player::raiseScore(int delta) {score_ += delta;}

void Player::loseLife() {if(lives_ > 0) lives_ -= 1;} 

int Player::getLives() const {return lives_;}
int Player::getScore() const {return score_;}
int Player::getLevel() const {return level_;}