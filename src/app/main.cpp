// at last
#include "Controller.h"
#include "LevelBuilder.h"
#include "Renderer.h"
#include "World.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>


namespace {
constexpr unsigned windowWidth = 800;
constexpr unsigned windowHeight = 600;
constexpr float maxDt = 1.0f / 30.0f;

World createWorld() {
    const vector2d arenaSize{windowWidth, windowHeight};
    
    // for now a block of bricks in the middle 
    std::vector<int> layout(COLUMNS * ROWS, 0);
    for (int row = 0; row < 6; ++row) {
        for (int column = 1; column < COLUMNS-1; ++column) {
            layout[row * COLUMNS + column] = 1;
        }
    }

    return World(Ball({0.f, 0.f}, {0.f, 0.f}, 8.f),           
                Arena(arenaSize),
                Player(),
                Paddle({350.f, windowHeight * .95f}, {100.f, 10.f}, 600.f, 0.f, arenaSize.x),
                buildLevel(layout, arenaSize));
}

int run() {
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Arkanoid");
    window.setFramerateLimit(60);

    World world = createWorld();
    const Controller controller;
    const Renderer renderer;
    sf::Clock clock;

    while (window.isOpen()) {
        const float dt = std::min(clock.restart().asSeconds(), maxDt);

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) window.close();
            }
            controller.handleEvent(*event, world);
        }
        if (window.hasFocus()) controller.update(world, dt);

        world.tick(dt);

        window.clear(sf::Color(20, 20, 20));
        renderer.drawAll(window, world);
        window.display();
    }
    return 0;
}
}

int main() {
    try {
        return run();
    } catch (const std::exception& error) {
        std::cerr << "Fatal error: " << error.what() << '\n';
        return 1;
    }
}