#include "MiniMap.hpp"

MiniMap::MiniMap(World& world, Camera& camera, sf::Vector2f position, sf::Vector2f scale, double multiply, sf::Color background_color, sf::Color outline_color, sf::Color tile_color)
: world(world), camera(camera), position(position), scale(scale), multiply(multiply), background_color(background_color), outline_color(outline_color), tile_color(tile_color){}

void MiniMap::draw(sf::RenderWindow& window)
{

    unsigned int tile_size = world.get_tile_size()*multiply;

    draw_background(window);

    for (rc::Coords crd: world.get_walls_coords())
    {
        sf::RectangleShape r{{tile_size, tile_size }};

        r.setPosition({(crd.x) * tile_size - camera.get_position().x*multiply + scale.x/2+position.x,
                        (crd.y) * tile_size - camera.get_position().y*multiply + scale.y/2+position.y});

        if ((r.getPosition().x+tile_size > position.x && r.getPosition().x < scale.x-tile_size+position.x)&&
            (r.getPosition().y+tile_size > position.y && r.getPosition().y < scale.y-tile_size+position.y))
            {
                r.setFillColor(tile_color);
                window.draw(r);
            }
    }

    draw_outline(window);

    for (auto ray: camera.get_rays_buf()){
        Camera::draw_line(window,{scale.x/2+position.x, scale.y/2+position.y},ray.first,{tile_size+position.x,tile_size+position.y},
        {scale.x-tile_size+position.x, scale.y-tile_size+position.y},ray.second, sf::Color::White,multiply);
    }
}

//Гетерры

double  MiniMap::get_multiply(){return multiply;}
sf::Vector2f MiniMap::get_scale(){return scale;}
sf::Vector2f MiniMap::get_position(){return position;}

sf::Color MiniMap::get_background_color(){return background_color;}
sf::Color MiniMap::get_outline_color(){return outline_color;}
sf::Color MiniMap::get_tile_color(){return tile_color;}

//Сеттеры

void MiniMap::set_multiply(double value){multiply = value;}
void MiniMap::set_scale(sf::Vector2f value){scale = value;}
void MiniMap::set_position(sf::Vector2f value){position = value;}

void MiniMap::set_background_color(sf::Color color){background_color= color;}
void MiniMap::set_outline_color(sf::Color color){outline_color = color;}
void MiniMap::set_tile_color(sf::Color color){tile_color = color;}

void MiniMap::draw_background(sf::RenderWindow& window)
{
    sf::RectangleShape background{scale};
    background.setFillColor(background_color);
    background.setPosition(position);
    window.draw(background);
}

void MiniMap::draw_outline(sf::RenderWindow& window)
{
    double tile_size = world.get_tile_size()*multiply;

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