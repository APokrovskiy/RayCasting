#include "Collider.hpp"

Collider::Collider(sf::Vector2f start,sf::Vector2f end):start(start), end(end){}


//Геттеры
sf::Vector2f Collider::get_start() const
{
    return start;
}

sf::Vector2f Collider::get_end() const
{
    return end;
}

sf::Vector2f Collider::get_collision_perpendicular(Collider& col, double error)
{
    sf::Vector2f perpendicular ={0,0};

    if(end.x >=col.get_start().x-error && end.x <=col.get_start().x+error)
    {
       perpendicular.x--;
    }
    else if(start.x <= col.get_end().x+error && start.x >= col.get_end().x-error)
    {
       perpendicular.x++;
    }
    if(end.y >= col.get_start().y-error && end.y <= col.get_start().y+error)
    {
        perpendicular.y--;
    }
    else if(start.y >= col.get_end().y-error && start.y <= col.get_end().y+error)
    {
        perpendicular.y++;
    }
    return perpendicular;
}

//Сеттеры
void Collider::set_start(sf::Vector2f start)
{
    this->start = start;
}

void Collider::set_end(sf::Vector2f end)
{
    this->end = end;
}

bool Collider::is_collised(Collider& col, double error)
{
    if(end.x < col.get_start().x-error or start.x > col.get_end().x+error){return false;}
    if(end.y < col.get_start().y-error or start.y > col.get_end().y+error){return false;}
    return true;
}