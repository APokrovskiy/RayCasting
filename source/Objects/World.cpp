#include "World.hpp"


// TODO: Реализовать конструкторы через перемещение
World::World(World_Map& wm, unsigned int tile): wm(wm), tile(tile){}
World::World(std::vector<std::string> wm, char wall,unsigned int tile): wm(rc::init_world_map(wm, wall)), tile(tile){} // TODO: передавать векторы по ссылке


void World::set_walls_coords(World_Map& wm)
{
    this->wm = wm;
}

void World::set_walls_coords(std::vector<std::string> wm, char wall)
{
    this->wm = rc::init_world_map(wm, wall);
}
void World::set_tile(unsigned int tile)
{
    this->tile = tile;
    if (tile <= 0)
        throw std::logic_error("tile <= 0\n");
}

void World::draw(sf::RenderWindow& win) const
{
    for (rc::Coords crd: wm)
    {
        sf::RectangleShape r{{tile, tile}};
        r.setPosition({crd.x * tile,crd.y * tile});
        r.setFillColor(sf::Color::Cyan);
        win.draw(r);
    }
}
