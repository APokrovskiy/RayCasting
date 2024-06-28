#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "World.hpp"

class Map
{
public:

    Map(World& world, Camera& camera,sf::Vector2f position,double multiply, sf::Color tile_color);

    void draw(sf::RenderWindow& window);

    //Геттеры

    double  get_multiply();
    sf::Vector2f get_position();
    sf::Color get_tile_color();

    //Сеттеры

    void set_multiply(double value);
    void set_position(sf::Vector2f value);
    void set_tile_color(sf::Color color);

private:

    sf::Color tile_color;
    sf::Vector2f position;
    double multiply;

    World& world;
    Camera& camera;
};