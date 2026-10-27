#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Arkanoid - Setup Test");
    window.setFramerateLimit(60);

    std::cout << "Okno SFML zostalo pomyślnie utworzone!\n";

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}