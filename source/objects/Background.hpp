#pragma once
#include <SFML/Graphics.hpp>
#include "settings.hpp"

class Background
{
public:
    Background(unsigned w, unsigned h)
    {
        clouds.setFillColor(sf::Color{0, 0, 100});
        floor.setFillColor(sf::Color{0, 100, 0});
        clouds.setSize({w, h / 2});
        floor.setSize({w, h / 2});
        floor.setPosition({0, h / 2});
    }

    void draw(sf::RenderWindow &win)
    {
        win.draw(floor);
        win.draw(clouds);
    }

    void update(unsigned w, unsigned h)
    {
        floor.setPosition({0, h / 2});
        clouds.setSize({w, h / 2});
        floor.setSize({w, h / 2});
    }

private:
    sf::RectangleShape clouds;
    sf::RectangleShape floor;
};
