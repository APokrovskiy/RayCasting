#pragma once
#include "ray-cast.hpp"

// TODO: Затем убрать зависимость из CMakeLists.txt

class Collider
{
public:
    Collider(rc::Coords start, rc::Coords end);

    // Геттеры
    // точка от которой начинается коллайдек
    rc::Coords get_start() const;
    // точка в которой заканчивается коллайдер
    rc::Coords get_end() const;
    // вектор противоположный направлению косания
    rc::Coords get_collision_perpendicular(Collider &col, double error);

    // Сеттеры
    void set_start(rc::Coords start);
    void set_end(rc::Coords end);

    // столкнулся ли этот колайдер с col
    bool is_collised(Collider &col, double error);

private:
    rc::Coords start;
    rc::Coords end;
};