#pragma once
#include <SFML/Graphics.hpp>
#include "settings.hpp" 

class Background
{
public:
    Background(ray_casting_settings& settings) : settings(settings)
    {
        clouds.setFillColor(sf::Color{0,0,100});
        floor.setFillColor(sf::Color{0,100,0});
        clouds.setSize({settings.win.screen_width, settings.win.screen_height / 2});
        floor.setSize({settings.win.screen_width, settings.win.screen_height / 2});
        floor.setPosition({0,  settings.win.screen_height / 2});
    }

    void draw(sf::RenderWindow& win)
    { 
        win.draw(floor);
        win.draw(clouds);
    }

    void update()
    {
        floor.setPosition({0,  settings.win.screen_height / 2});
        clouds.setSize({settings.win.screen_width, settings.win.screen_height / 2});
        floor.setSize({settings.win.screen_width, settings.win.screen_height / 2});
    }

private:
    ray_casting_settings& settings;

    sf::RectangleShape clouds;
    sf::RectangleShape floor;
};

