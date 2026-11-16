#pragma once
#include "World.h"
#include <SFML/Window.hpp>


class Controller {
    private:
        sf::Keyboard::Key left_ = sf::Keyboard::Key::Left;
        sf::Keyboard::Key right_ = sf::Keyboard::Key::Right;
        sf::Keyboard::Key launch_ = sf::Keyboard::Key::Space;
        sf::Keyboard::Key confirm_ = sf::Keyboard::Key::Enter;

    public:
        // for events, like launching ball or restarting
        void handleEvent(const sf::Event& event, World& world) const;
        // for moving the paddle
        void update(World& world, float dt) const;
};