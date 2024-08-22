#pragma once

#include <SFML/Graphics.hpp>

#include "cmr.hpp"
#include "world.hpp"

class MiniMap
{
public:

    MiniMap(World *world, Camera *camera);

    void draw(sf::RenderWindow& window);
    //Гетерры

    double  get_multiply();
    sf::Vector2f get_scale();
    sf::Vector2f get_position();


    //Сеттеры
    void set_camera(Camera *cmr);
    void set_world(World *world);

    void set_multiply(double value);
    void set_scale(sf::Vector2f value);
    void set_position(sf::Vector2f value);



private:

    void draw_background(sf::RenderWindow& window);
    void draw_outline(sf::RenderWindow& window);

    sf::Color background_color {200,200,200};
    sf::Color outline_color {100, 100, 100};
    sf::Color tile_color{sf::Color::Black};

    sf::Vector2f position{0,0};
    sf::Vector2f scale {200,200};
    double multiply{0.1};
    

    World *world;
    Camera *camera;

};