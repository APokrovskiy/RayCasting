#include "Collider.hpp"

Collider::Collider(rc::Coords start, rc::Coords end) : start(start), end(end) {}

// Геттеры
rc::Coords Collider::get_start() const
{
    return start;
}

rc::Coords Collider::get_end() const
{
    return end;
}

rc::Coords Collider::get_collision_perpendicular(Collider &col, double error)
{
    rc::Coords perpendicular = {0, 0};
    // проверка на нужной ли высоте чтобы проверять по х
    if ((end.y > col.start.y && end.y < col.end.y) || (start.y > col.start.y && start.y < col.end.y))
    {
        // проверка на столкновение справа
        if (end.x >= col.get_start().x - error && end.x <= col.get_start().x + error)
        {
            perpendicular.x--;
        }
        // проверка на столкновение слева
        else if (start.x <= col.get_end().x + error && start.x >= col.get_end().x - error)
        {
            perpendicular.x++;
        }
    }
    // проверка на нужной ли высоте чтобы проверять по y
    if ((end.x > col.start.x && end.x < col.end.x) || (start.x > col.start.x && start.x < col.end.x))
    {
        // проверка на столкновение снизу
        if (end.y >= col.get_start().y - error && end.y <= col.get_start().y + error)
        {
            perpendicular.y--;
        }
        // проверка на столкновение сверху
        else if (start.y >= col.get_end().y - error && start.y <= col.get_end().y + error)
        {
            perpendicular.y++;
        }
    }
    return perpendicular;
}

// Сеттеры
void Collider::set_start(rc::Coords start)
{
    this->start = start;
}

void Collider::set_end(rc::Coords end)
{
    this->end = end;
}

bool Collider::is_collised(Collider &col, double error)
{
    if (end.x < col.get_start().x - error or start.x > col.get_end().x + error)
    {
        return false;
    }
    if (end.y < col.get_start().y - error or start.y > col.get_end().y + error)
    {
        return false;
    }
    return true;
}