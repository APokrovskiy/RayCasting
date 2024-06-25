#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:

    Collider(sf::Vector2f start,sf::Vector2f end);

    //Геттеры
    sf::Vector2f get_start() const;
    sf::Vector2f get_end() const;
    sf::Vector2f get_collision_perpendicular(Collider& col, double error);

    //Сеттеры
    void set_start(sf::Vector2f start);
    void set_end(sf::Vector2f end);

    // столкнулся ли этот колайдер с col
    bool is_collised(Collider& col,double error);

private:
    sf::Vector2f start;
    sf::Vector2f end;
};