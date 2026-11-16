#include "Renderer.h"

namespace {
    sf::Vector2f vectorSFML(vector2d v) {return {v.x, v.y};}

    // will do different colors based on bricks hp (red=3, yellow=2, green=1)
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

void Renderer::drawAll(sf::RenderTarget& target, const World& world) const {
    drawBricks(target, world);
    drawPaddle(target, world);
    drawBall(target, world);
    drawLives(target, world);
    drawScore(target, world);
    drawStateOverlay(target, world);
}

Renderer::Renderer(const std::filesystem::path& fontPath) {
    // explains itself. If !font: raiseErr
    if (!font.openFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font");
    } 
}

void Renderer::drawText(sf::RenderTarget& target, const std::string& string, unsigned textSize,sf::Vector2f position, float alignment) const {
    sf::Text text(font, string, textSize);
    
    const sf::FloatRect textBox = text.getLocalBounds();
    text.setOrigin({textBox.position.x + textBox.size.x * alignment, textBox.position.y});
    text.setPosition(position);

    text.setFillColor(sf::Color::White);

    target.draw(text);
}

void Renderer::drawScore(sf::RenderTarget& target, const World& world) const {
    const float rightEdge = target.getView().getSize().x - 10.f; //leave some margin
 
    drawText(target, "Score: " + std::to_string(world.player().getScore()), 22, {rightEdge, 8.f}, 1.0f);
}

void Renderer::drawStateOverlay(sf::RenderTarget& target, const World& world) const {
    const sf::Vector2f size = target.getView().getSize();
 
    sf::Color tint;
    std::string message;
 
    switch (world.state()) {
        case GameState::Serving:
            drawText(target, "Press SPACE to start", 20, {size.x / 2.f, size.y * 0.6f}, 0.5f);
            return;
        case GameState::Playing:
            return;
        case GameState::GameOver:
            tint = sf::Color(200, 40, 40, 120);
            message = "GAME OVER";
            break;
        case GameState::Cleared:
            tint = sf::Color(40, 200, 40, 120);
            message = "LEVEL CLEARED";
            break;
    }
 
    sf::RectangleShape overlay(size);
    overlay.setFillColor(tint);
    target.draw(overlay);
 
    drawText(target, message, 48, {size.x / 2.f, size.y * 0.4f}, 0.5f);
    const std::string hint = (world.state() == GameState::GameOver) ? "Press ENTER to restart": "Press ENTER to continue";
    drawText(target, hint, 20, {size.x / 2.f, size.y * 0.4f + 70.f}, 0.5f);
}