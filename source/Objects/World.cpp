#include "World.hpp"

// TODO: Реализовать конструкторы через перемещение
World::World(World_Map &wm, unsigned int tile) : wm(wm), tile(tile)
{
    for (auto crd : wm)
        wall_colliders.push_back(Collider({crd.x * tile, crd.y * tile}, {(crd.x + 1) * tile, (crd.y + 1) * tile})); // TODO: Устранить повторения
}

World::World(std::vector<std::string> wm, char wall, unsigned int tile) : wm(rc::init_world_map(wm, wall)), tile(tile)
{
    for (auto crd : this->wm)
        wall_colliders.push_back(Collider({crd.x * tile, crd.y * tile}, {(crd.x + 1) * tile, (crd.y + 1) * tile})); // TODO: Устранить повторения

} // TODO: передавать векторы по ссылке

void World::set_walls_coords(World_Map &wm)
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

void World::draw(sf::RenderWindow &win) const
{
    for (rc::Coords crd : wm)
    {
        sf::RectangleShape r{{tile, tile}};
        r.setPosition({crd.x * tile, crd.y * tile});
        r.setFillColor(sf::Color::Cyan);
        win.draw(r);
    }
}

void World::draw_background(sf::RenderWindow& win,float map_size,float tile_on_map)
{
    sf::RectangleShape background{{map_size+tile_on_map,map_size+tile_on_map}};
    background.setFillColor({80,80,80});
    win.draw(background);
}

void World::draw_out_line_background(sf::RenderWindow& win,float map_size,float tile_on_map)
{
    sf::RectangleShape side_out_line_background{{tile_on_map,map_size+tile_on_map}};
    side_out_line_background.setFillColor({100,100,100});

    sf::RectangleShape top_and_bottom_out_line_background{{map_size+tile_on_map*2,tile_on_map}};
    top_and_bottom_out_line_background.setFillColor({100,100,100});
    
    win.draw(side_out_line_background);

    side_out_line_background.setPosition(map_size+tile_on_map,0);
    win.draw(side_out_line_background);

    win.draw(top_and_bottom_out_line_background);

    top_and_bottom_out_line_background.setPosition(0,map_size+tile_on_map);
    win.draw(top_and_bottom_out_line_background);
}

void World::draw_map(sf::RenderWindow& win,float multiply,float map_size,sf::Vector2f pos)
{
    if (multiply < 0 || multiply > 1) throw std::logic_error("multiply is not correct");

    draw_background(win,map_size,tile*multiply);

    for (rc::Coords crd: wm)
    {
        sf::RectangleShape r{{tile*multiply, tile*multiply}};
        r.setPosition({(crd.x * tile - pos.x + tile)*multiply + map_size/2,
                        (crd.y * tile - pos.y + tile)*multiply+ map_size/2});

        if ((r.getPosition().x+tile*multiply > 0 && r.getPosition().x < map_size+tile*multiply)&&
            (r.getPosition().y+tile*multiply > 0 && r.getPosition().y < map_size+tile*multiply))
        {
            r.setFillColor(sf::Color::Cyan);
            win.draw(r);
        }
    }

    draw_out_line_background(win,map_size,tile*multiply);
}