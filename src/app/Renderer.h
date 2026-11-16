#pragma once
#include "World.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>
 
class Renderer {
    private:
        sf::Font font; 

        // helper function - creates text with given text (wow), of given font size, at given position aligned
        //alignment: 0 - text aligned left, 0.5 - middle, 1 - right
        void drawText(sf::RenderTarget& target, const std::string& string, unsigned textSize,sf::Vector2f position, float alignment=0.f) const;

        void drawBricks(sf::RenderTarget& target, const World& world) const;
        void drawPaddle(sf::RenderTarget& target, const World& world) const;
        void drawBall(sf::RenderTarget& target, const World& world) const;
        void drawLives(sf::RenderTarget& target, const World& world) const;
        void drawStateOverlay(sf::RenderTarget& target, const World& world) const;
        void drawScore(sf::RenderTarget& target, const World& world) const;

        
 
    public: 
        Renderer(const std::filesystem::path& fontPath);

        // takes all the other private drawing methods and puts them on screen
        void drawAll(sf::RenderTarget& target, const World& world) const;
};
 