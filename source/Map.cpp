#include "Map.hpp"

Map::Map(World& world, Camera& camera, sf::Color background_color, sf::Color outline_color, sf::Color tile_color): world(world),camera(camera)
 {
    this->background_color=background_color;
    this->outline_color=outline_color;
    this->tile_color=tile_color;
 }

static void draw_line(sf::RenderWindow& w,rc::Coords cmr, int dist,int max_dist, double rot_angle, sf::Color color,double multiply = 1)
{
    dist *=multiply;

    if(dist>max_dist)
    {
        dist = max_dist;
    }

    rot_angle = rc::radians_normalise(rot_angle);

    sf::VertexArray line{ sf::Lines, 2 };
    line[0] = sf::Vector2f{cmr.x, cmr.y};
    line[1] = sf::Vector2f{cmr.x + dist * cos(rot_angle), cmr.y - dist * sin(rot_angle) };
    line[0].color = color;
    line[1].color = color;
    w.draw(line);
}

void Map::draw_map(sf::RenderWindow& window, double multiply, unsigned int size, sf::Vector2f pos)
{
    unsigned int tile_size = world.get_tile_size()*multiply;

    for (rc::Coords crd: world.get_walls_coords())
    {
        sf::RectangleShape r{{tile_size, tile_size }};

        r.setPosition({(crd.x+1) * tile_size + pos.x,
                        (crd.y+1) * tile_size + pos.y});


        if ((r.getPosition().x+tile_size > 0 && r.getPosition().x < window.getSize().x)&&
            (r.getPosition().y+tile_size > 0 && r.getPosition().y < window.getSize().y))

        r.setFillColor(tile_color);
        window.draw(r);

    }

    for (auto ray: camera.get_rays_buf()){
        draw_line(window,{camera.get_position().x*multiply + pos.x+tile_size, camera.get_position().y*multiply + pos.y +tile_size},
                ray.first, ray.first,ray.second, sf::Color::White,multiply);
    }

}

void Map::draw_minimap(sf::RenderWindow& window, double multiply, unsigned int size, sf::Vector2f pos)
{
    unsigned int tile_size = world.get_tile_size()*multiply;

    draw_background(window, size, pos);

    for (rc::Coords crd: world.get_walls_coords())
    {
        sf::RectangleShape r{{tile_size, tile_size }};

        r.setPosition({(crd.x) * tile_size - camera.get_position().x*multiply + size/2+pos.x,
                        (crd.y) * tile_size - camera.get_position().y*multiply + size/2+pos.y});

        if ((r.getPosition().x+tile_size > pos.x && r.getPosition().x < size-tile_size+pos.x)&&
            (r.getPosition().y+tile_size > pos.y && r.getPosition().y < size-tile_size+pos.y))
            {
                r.setFillColor(tile_color);
                window.draw(r);
            }
    }

    draw_outline(window, size, tile_size, pos);

    for (auto ray: camera.get_rays_buf()){
        draw_line(window,{size/2+pos.x, size/2+pos.y},ray.first, size/2 - tile_size,ray.second, sf::Color::White,multiply);
    }
}

void Map::draw_background(sf::RenderWindow& window, unsigned int size, sf::Vector2f pos)
{
    sf::RectangleShape background{{size,size}};
    background.setFillColor(background_color);
    background.setPosition(pos);
    window.draw(background);
}

void Map::draw_outline(sf::RenderWindow& window, unsigned int size, double tile_on_map, sf::Vector2f pos)
{
    sf::RectangleShape side_out_line_background{{tile_on_map,size}};
        side_out_line_background.setFillColor(outline_color);
        side_out_line_background.setPosition(pos);

        sf::RectangleShape top_and_bottom_out_line_background{{size,tile_on_map}};
        top_and_bottom_out_line_background.setFillColor(outline_color);
        top_and_bottom_out_line_background.setPosition(pos);
        
        window.draw(side_out_line_background);

        side_out_line_background.setPosition(size-tile_on_map+pos.x,pos.y);
        window.draw(side_out_line_background);

        window.draw(top_and_bottom_out_line_background);

        top_and_bottom_out_line_background.setPosition(pos.x,size-tile_on_map+pos.y);
        window.draw(top_and_bottom_out_line_background);
}

