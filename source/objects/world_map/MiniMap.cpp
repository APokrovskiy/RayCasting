#include "world_map/MiniMap.hpp"

MiniMap::MiniMap(World *world, Camera *cmr)
    :world(world), camera(cmr)
{
    if (!world || !camera) throw std::runtime_error("minimap arg has null ptr");
}

void MiniMap::draw(sf::RenderWindow& window)
{

    unsigned int tile_size = world->get_tile_size()*multiply;

    draw_background(window);

    for (rc::Coords crd: world->get_walls_coords())
    {
        sf::RectangleShape r{{tile_size, tile_size }};

        r.setPosition({(crd.x) * tile_size - camera->get_position().x*multiply + scale.x/2+position.x,
                        (crd.y) * tile_size - camera->get_position().y*multiply + scale.y/2+position.y});

        if ((r.getPosition().x+tile_size > position.x && r.getPosition().x < scale.x-tile_size+position.x)&&
            (r.getPosition().y+tile_size > position.y && r.getPosition().y < scale.y-tile_size+position.y))
            {
                r.setFillColor(tile_color);
                window.draw(r);
            }
    }

    draw_outline(window);

    for (auto ray: camera->get_rays_buf()){
        Camera::draw_line(window,{scale.x/2+position.x, scale.y/2+position.y},ray.first,{tile_size+position.x,tile_size+position.y},
        {scale.x-tile_size+position.x, scale.y-tile_size+position.y},ray.second, sf::Color::White,multiply);
    }
}

//Гетерры

double  MiniMap::get_multiply(){return multiply;}
sf::Vector2f MiniMap::get_scale(){return scale;}
sf::Vector2f MiniMap::get_position(){return position;}


//Сеттеры
void MiniMap::set_camera(Camera *c)
{
    if (c) camera = c;
    else throw std::runtime_error("camera ptr has null");
}
void MiniMap::set_world(World *w)
{
    if (w) world = w;
    else throw std::runtime_error("world ptr has null");
}
void MiniMap::set_multiply(double value){multiply = value;}
void MiniMap::set_scale(sf::Vector2f value){scale = value;}
void MiniMap::set_position(sf::Vector2f value){position = value;}

void MiniMap::draw_background(sf::RenderWindow& window)
{
    sf::RectangleShape background{scale};
    background.setFillColor(background_color);
    background.setPosition(position);
    window.draw(background);
}

void MiniMap::draw_outline(sf::RenderWindow& window)
{
    double tile_size = world->get_tile_size()*multiply;

    sf::RectangleShape side_out_line_background{{tile_size,scale.y}};
    side_out_line_background.setFillColor(outline_color);
    side_out_line_background.setPosition(position);

    sf::RectangleShape top_and_bottom_out_line_background{{scale.x,tile_size}};
    top_and_bottom_out_line_background.setFillColor(outline_color);
    top_and_bottom_out_line_background.setPosition(position);
        
    window.draw(side_out_line_background);

    side_out_line_background.setPosition(scale.x-tile_size+position.x, position.y);
    window.draw(side_out_line_background);

    window.draw(top_and_bottom_out_line_background);

    top_and_bottom_out_line_background.setPosition(position.x,scale.y-tile_size+position.y);
    window.draw(top_and_bottom_out_line_background);
}