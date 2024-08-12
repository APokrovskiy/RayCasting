#include "world_map/Map.hpp"

Map::Map(World * w, Camera * c)
    :world(w), camera(c)
{
    if (!w || !c) throw std::runtime_error("map arg has null ptr");
}

void Map::draw(sf::RenderWindow &window)
{
    unsigned int tile_size = world->get_tile_size() * multiply;

    sf::RectangleShape background{{window.getSize().x, window.getSize().y}};
    background.setFillColor(background_color);
    window.draw(background);
    for (rc::Coords crd : world->get_walls_coords())
    {
        sf::RectangleShape r{{tile_size, tile_size}};

        r.setPosition({(crd.x + 1) * tile_size + position.x,
                       (crd.y + 1) * tile_size + position.y});

        if ((r.getPosition().x + tile_size > 0 && r.getPosition().x < window.getSize().x) &&
            (r.getPosition().y + tile_size > 0 && r.getPosition().y < window.getSize().y))

            r.setFillColor(tile_color);
        window.draw(r);
    }

    for (auto ray : camera->get_rays_buf())
    {
        Camera::draw_line(window, {camera->get_position().x * multiply + position.x + tile_size, camera->get_position().y * multiply + position.y + tile_size},
                        ray.first, {0, 0}, {window.getSize().x, window.getSize().y}, ray.second, sf::Color::White, multiply);
    }
}

void Map::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        position.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        position.x += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        position.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        position.x -= speed;
    }
}

// Геттеры

double Map::get_multiply() { return multiply; }
sf::Vector2f Map::get_position() { return position; }


// Сеттеры
void Map::set_camera(Camera *c)
{
    if (c) camera = c;
    else throw std::runtime_error("camera ptr has null");
}
void Map::set_world(World *w)
{
    if (w) world = w;
    else throw std::runtime_error("world ptr has null");
}

void Map::set_multiply(double value) { multiply = value; }
void Map::set_position(sf::Vector2f value) { position = value; }
