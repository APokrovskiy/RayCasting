#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "World.hpp"

class Map
{
public:
    // Map(World &world, Camera &camera, sf::Vector2f position, double multiply, sf::Color tile_color, sf::Color background_color, double speed);
    Map(World *, Camera *);

    void draw(sf::RenderWindow &window);

    void move();

    // Геттеры
    double get_multiply();
    sf::Vector2f get_position();

    // Сеттеры
    void set_camera(Camera *cmr);
    void set_world(World *world);
    void set_multiply(double value);
    void set_position(sf::Vector2f value);

private:
    sf::Color tile_color{20, 20, 20};
    sf::Color background_color{100, 100, 100};
    sf::Vector2f position{0,0};
    double multiply{1};
    double speed{10};

    World *world;
    Camera *camera;
};