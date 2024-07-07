#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "World.hpp"

class Map
{
public:
    Map(World &world, Camera &camera, sf::Vector2f position, double multiply, sf::Color tile_color, sf::Color background_color, double speed);

    void draw(sf::RenderWindow &window);

    void move();

    // Геттеры

    double get_multiply();
    sf::Vector2f get_position();
    sf::Color get_tile_color();
    sf::Color get_background_color();

    // Сеттеры

    void set_multiply(double value);
    void set_position(sf::Vector2f value);
    void set_tile_color(sf::Color color);
    void set_background_color(sf::Color color);

private:
    sf::Color tile_color;
    sf::Color background_color;
    sf::Vector2f position;
    double multiply;
    double speed;

    World &world;
    Camera &camera;
};