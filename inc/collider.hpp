#pragma once
#include <SFML/Graphics.hpp>

// TODO: Заменить sf::Vector2f на rc::Coords, Ядро не должно зависеть от каких либо библиотек.
// TODO: Затем убрать зависимость из CMakeLists.txt

class Collider
{
public:
    Collider(sf::Vector2f start, sf::Vector2f end);

    // Геттеры
    // точка от которой начинается коллайдек
    sf::Vector2f get_start() const;
    // точка в которой заканчивается коллайдер
    sf::Vector2f get_end() const;
    // вектор противоположный направлению косания
    sf::Vector2f get_collision_perpendicular(Collider &col, double error);

    // Сеттеры
    void set_start(sf::Vector2f start);
    void set_end(sf::Vector2f end);

    // столкнулся ли этот колайдер с col
    bool is_collised(Collider &col, double error);

private:
    sf::Vector2f start;
    sf::Vector2f end;
};