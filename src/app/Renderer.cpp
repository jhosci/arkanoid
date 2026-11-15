#include "Renderer.h"

namespace {
    sf::Vector2f vectorSFML(vector2d v) {return {v.x, v.y};}

    // will do different colors based on bricks hp
    sf::Color brickColor(int hp) {
        switch (hp)
        {
        case 1:
            return sf::Color(90, 200, 120);
        case 2:
            return sf::Color(240, 200, 80);
        case 3:
            return sf::Color(230, 120, 70);
        default:
            return sf::Color(200, 70, 90);
        }
    }
}

void Renderer::drawBricks(sf::RenderTarget& target, const World& world) const {
    sf::RectangleShape rectangle;

    // for(var : collection) like for i in iterable in python 
    for (const auto& brick : world.bricks()) {
        const vector2d position = brick->getPosition();
        const vector2d size = brick->getSize();

        rectangle.setPosition(vectorSFML(brick->getPosition()));
        rectangle.setSize(vectorSFML(brick->getSize()));
        rectangle.setFillColor(brickColor(brick->getHp()));

        target.draw(rectangle);
    }
}

void Renderer::drawPaddle(sf::RenderTarget& target, const World& world) const {
    sf::RectangleShape rectangle;

    const Paddle &paddle = world.paddle();

    const vector2d position = paddle.getPosition();
    const vector2d size = paddle.getSize();

    rectangle.setPosition(vectorSFML(position));
    rectangle.setSize(vectorSFML(size));
    rectangle.setFillColor(sf::Color::Red);

    target.draw(rectangle);
}

void Renderer::drawBall(sf::RenderTarget& target, const World& world) const {
    sf::CircleShape circle;

    const Ball &ball = world.ball();

    const vector2d position = ball.getPosition();
    const float radius = ball.getRadius();

    circle.setOrigin(vectorSFML({radius, radius}));
    circle.setPosition(vectorSFML(ball.getPosition()));
    circle.setRadius(radius);

    circle.setFillColor(sf::Color::White);

    target.draw(circle);
}

void Renderer::drawLives(sf::RenderTarget& target, const World& world) const {
    float rad = 6.0f; float spacing = 18.0f;

    sf::CircleShape life;
    life.setRadius(rad);
    life.setFillColor(sf::Color::Red);

    for (int i = 0; i < world.player().getLives(); i++) {
        life.setPosition({10.0f + i * spacing, 10.0f});

        target.draw(life);
    }
}

void Renderer::drawStateOverlay(sf::RenderTarget& target, const World& world) const {
    const sf::Vector2f size = target.getView().getSize();
 
    sf::Color tint;
    std::string message;
 
    switch (world.state()) {
        case GameState::Serving:
            return;
        case GameState::Playing:
            return;
        case GameState::GameOver:
            tint = sf::Color(200, 40, 40, 120);
            break;
        case GameState::Cleared:
            tint = sf::Color(40, 200, 80, 100);
            break;
    }

    sf::RectangleShape overlay(size);
    overlay.setFillColor(tint);
    target.draw(overlay);
 
}

void Renderer::drawAll(sf::RenderTarget& target, const World& world) const {
    drawBricks(target, world);
    drawPaddle(target, world);
    drawBall(target, world);
    drawLives(target, world);
    drawStateOverlay(target, world);
}