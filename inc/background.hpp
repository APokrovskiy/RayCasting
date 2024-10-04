#pragma once
#include <SFML/Graphics.hpp>
#include "setts/setts.hpp"

class Background
{
public:
    Background(unsigned w, unsigned h)
    {
        clouds.setFillColor(sf::Color{0, 0, 100});
        floor.setFillColor(sf::Color{0, 100, 0});
        clouds.setSize({static_cast<float>(w),static_cast<float>(h / 2)});
        floor.setSize({ static_cast<float>(w), static_cast<float>(h / 2)});
        floor.setPosition({0.0f, static_cast<float>(h / 2)});
    }

    void draw(sf::RenderWindow &win)
    {
        win.draw(floor);
        win.draw(clouds);
    }

    void update(unsigned w, unsigned h)
    {
        floor.setPosition({0.0f, static_cast<float>(h / 2)});
        clouds.setSize({ static_cast<float>(w), static_cast<float>(h / 2)});
        floor.setSize({ static_cast<float>(w), static_cast<float>(h / 2)});
    }

private:
    sf::RectangleShape clouds;
    sf::RectangleShape floor;
};
