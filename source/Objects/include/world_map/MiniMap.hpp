#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "World.hpp"

class MiniMap
{
public:

    MiniMap(World& world, Camera& camera, sf::Vector2f position, sf::Vector2f scale, double multiply, sf::Color background_color, sf::Color outline_color, sf::Color tile_color);

    void draw(sf::RenderWindow& window);
    //Гетерры

    double  get_multiply();
    sf::Vector2f get_scale();
    sf::Vector2f get_position();

    sf::Color get_background_color();
    sf::Color get_outline_color();
    sf::Color get_tile_color();

    //Сеттеры

    void set_multiply(double value);
    void set_scale(sf::Vector2f value);
    void set_position(sf::Vector2f value);

    void set_background_color(sf::Color color);
    void set_outline_color(sf::Color color);
    void set_tile_color(sf::Color color);

private:

    void draw_background(sf::RenderWindow& window);
    void draw_outline(sf::RenderWindow& window);

    sf::Color background_color;
    sf::Color outline_color;
    sf::Color tile_color;

    sf::Vector2f position;
    sf::Vector2f scale;
    double multiply;
    

    World& world;
    Camera& camera;

};