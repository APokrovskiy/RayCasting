#include "world_map/Map.hpp"

Map::Map(World &world, Camera &camera, sf::Vector2f position, double multiply, sf::Color tile_color, sf::Color background_color, double speed = 1)
    : world(world), camera(camera), position(position), multiply(multiply), tile_color(tile_color), background_color(background_color), speed(speed) {}

void Map::draw(sf::RenderWindow &window)
{
    unsigned int tile_size = world.get_tile_size() * multiply;

    sf::RectangleShape background{{window.getSize().x, window.getSize().y}};
    background.setFillColor(background_color);
    window.draw(background);
    for (rc::Coords crd : world.get_walls_coords())
    {
        sf::RectangleShape r{{tile_size, tile_size}};

        r.setPosition({(crd.x + 1) * tile_size + position.x,
                       (crd.y + 1) * tile_size + position.y});

        if ((r.getPosition().x + tile_size > 0 && r.getPosition().x < window.getSize().x) &&
            (r.getPosition().y + tile_size > 0 && r.getPosition().y < window.getSize().y))

            r.setFillColor(tile_color);
        window.draw(r);
    }

    for (auto ray : camera.get_rays_buf())
    {
        Camera::draw_line(window, {camera.get_position().x * multiply + position.x + tile_size, camera.get_position().y * multiply + position.y + tile_size},
                          ray.first, {0, 0}, {window.getSize().x, window.getSize().y}, ray.second, sf::Color::White, multiply);
    }
}

void Map::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        position.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        position.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        position.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        position.x += speed;
    }
}

// Геттеры

double Map::get_multiply() { return multiply; }
sf::Vector2f Map::get_position() { return position; }
sf::Color Map::get_tile_color() { return tile_color; }
sf::Color Map::get_background_color() { return background_color; }

// Сеттеры

void Map::set_multiply(double value) { multiply = value; }
void Map::set_position(sf::Vector2f value) { position = value; }
void Map::set_tile_color(sf::Color color) { tile_color = color; }
void Map::set_background_color(sf::Color color) { background_color = color; }