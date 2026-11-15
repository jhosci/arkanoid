#pragma once
#include "World.h"
#include <SFML/Graphics.hpp>
 
class Renderer {
    private:
        void drawBricks(sf::RenderTarget& target, const World& world) const;
        void drawPaddle(sf::RenderTarget& target, const World& world) const;
        void drawBall(sf::RenderTarget& target, const World& world) const;
        void drawLives(sf::RenderTarget& target, const World& world) const;
        void drawStateOverlay(sf::RenderTarget& target, const World& world) const;
 
    public: 
        void drawAll(sf::RenderTarget& target, const World& world) const;
};
 