#include "Controller.h"

void Controller::handleEvent(const sf::Event& event, World& world) const {
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        if (key->code == launch_) world.launchBall();
        if (key->code == confirm_) {world.restart(); world.startNextLevel();} // they won't execute together anyways
    }
}

void Controller::update(World& world, float dt) const {
    if (sf::Keyboard::isKeyPressed(left_))  world.movePaddleLeft(dt);
    if (sf::Keyboard::isKeyPressed(right_)) world.movePaddleRight(dt);
}