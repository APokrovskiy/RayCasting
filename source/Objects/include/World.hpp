#pragma once

#include <set>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ray-cast.hpp"
#include "Collider.hpp"

class World
{
public:
    using World_Map = std::set<rc::Coords>;
    using World_String_Map = std::vector<std::string>;

    // TODO: Реализовать конструкторы через перемещение
    World(World_Map &wm, unsigned int tile);
    World(std::vector<std::string> wm, char wall, unsigned int tile); // TODO: передавать векторы по ссылке

    const std::vector<Collider> &get_colliders() { return wall_colliders; }
    const World_Map &get_walls_coords() const { return wm; }
    unsigned int get_tile_size() const { return tile; }

    void set_walls_coords(World_Map &wm);
    void set_walls_coords(std::vector<std::string> wm, char wall);
    void set_tile(unsigned int tile);

    void draw(sf::RenderWindow &win) const;

private:
    World_Map wm;
    unsigned int tile;

    std::vector<Collider> wall_colliders;
};