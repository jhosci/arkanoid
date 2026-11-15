#pragma once
#include "World.h"
#include <SFML/Window.hpp>


class Controller {
    private:
        sf::Keyboard::Key left_ = sf::Keyboard::Key::Left;
        sf::Keyboard::Key right_ = sf::Keyboard::Key::Right;
        sf::Keyboard::Key launch_ = sf::Keyboard::Key::Space;

    public:
        void handleEvent(const sf::Event& event, World& world) const;

        void update(World& world, float dt) const;
};