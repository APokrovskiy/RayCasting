#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "World.hpp"

class Map
{
public:

    Map(World& world, Camera& camera, sf::Color background_color, sf::Color outline_color, sf::Color tile_color);

    void draw_map(sf::RenderWindow& window, double multiply, unsigned int size, sf::Vector2f pos);
    void draw_minimap(sf::RenderWindow& window, double multiply, unsigned int size, sf::Vector2f pos);

private:

    void draw_background(sf::RenderWindow& window, unsigned int size, sf::Vector2f pos);
    void draw_outline(sf::RenderWindow& window, unsigned int size, double tile_on_map, sf::Vector2f pos);

    sf::Color background_color;
    sf::Color outline_color;
    sf::Color tile_color;
    World& world;
    Camera& camera;
};