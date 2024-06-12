#pragma once

#include <set>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ray-cast.hpp"



class World
{
public:
    using World_Map = std::set<rc::Coords>;

    World(World_Map& wm, unsigned int tile): wm(wm), tile(tile){}
    World(std::vector<std::string> wm, char wall,unsigned int tile): wm(rc::init_world_map(wm, wall)), tile(tile){}

    const World_Map& get_walls_coords(){return wm;}
    unsigned int get_tile_size(){return tile;}
    
    void draw(sf::RenderWindow& win)
    {
        for (rc::Coords crd: wm)
        {
            sf::RectangleShape r{{tile, tile}}; // TODO: Инициализация в цикле
            r.setPosition({crd.x * tile,crd.y * tile});
            r.setFillColor(sf::Color::Cyan);
            win.draw(r);
        }
    }

private:
    World_Map wm;
    unsigned int tile;
};