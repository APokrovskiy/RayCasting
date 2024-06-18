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
    
    //draw map
    void draw_map(sf::RenderWindow& win,float multiply,float map_size,sf::Vector2f pos,double rotation,unsigned int visual_range,double fov,int n_rays)
    {
        if (multiply < 0 || multiply > 1) throw std::logic_error("multiply is not correct");

        std::vector<std::pair<unsigned int, double>> rays_buf;

        sf::RectangleShape background{{(map_size+tile)*multiply,(map_size+tile)*multiply}};
        background.setFillColor({80,80,80});
        win.draw(background);

        for (rc::Coords crd: wm)
        {
            sf::RectangleShape r{{tile*multiply, tile*multiply}};
            r.setPosition({(crd.x * tile - pos.x + map_size/2)*multiply,
                           (crd.y * tile - pos.y + map_size/2)*multiply});

            if ((r.getPosition().x > 0 && r.getPosition().x < map_size*multiply)&&
                (r.getPosition().y > 0 && r.getPosition().y < map_size*multiply))
            {
                r.setFillColor(sf::Color::Cyan);
                win.draw(r);
            }
        }
        sf::CircleShape c{2};
        c.setPosition({map_size*multiply/2, map_size*multiply/2});
        c.setFillColor(sf::Color::Blue);
        win.draw(c);
    }
    

private:
    World_Map wm;
    unsigned int tile;
};