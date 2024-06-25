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

    World(World_Map& wm, unsigned int tile): wm(wm), tile(tile)
    {
        for(auto crd: wm)
        {
            wall_colliders.push_back(Collider({crd.x * tile,crd.y * tile},{(crd.x+1) * tile,(crd.y+1) * tile}));
        }
    }
    World(std::vector<std::string> wm, char wall,unsigned int tile): wm(rc::init_world_map(wm, wall)), tile(tile)
    {
        for(auto crd: this->wm)
        {
            wall_colliders.push_back(Collider({crd.x * tile,crd.y * tile},{(crd.x+1) * tile,(crd.y+1) * tile}));
        }
    }
    const std::vector<Collider>& get_colliders(){return wall_colliders;}
    const World_Map& get_walls_coords(){return wm;}
    unsigned int get_tile_size(){return tile;}
    
    void draw(sf::RenderWindow& win)
    {
        for (rc::Coords crd: wm)
        {
            sf::RectangleShape r{{tile, tile}};
            r.setPosition({crd.x * tile,crd.y * tile});
            r.setFillColor(sf::Color::Cyan);
            win.draw(r);
        }
    }

private:
    std::vector<Collider> wall_colliders;
    World_Map wm;
    unsigned int tile;
};