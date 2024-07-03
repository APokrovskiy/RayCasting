#include "Camera.hpp"
#include <iostream>
#include <exception>

Camera::Camera(World &w, int size) : world(w)
{
    side_square_size = size;
    col = Collider({pos.x - side_square_size / 2, pos.y - side_square_size / 2},
                   {pos.x + side_square_size / 2, pos.y + side_square_size / 2});
}

// Геттеры
sf::Vector2f Camera::get_position() const
{
    return pos;
}

double Camera::get_rotation() const
{
    return rot_a;
}

double Camera::get_speed() const
{
    return speed;
}

unsigned int Camera::get_n_rays() const
{
    return n_rays;
}

const std::vector<std::pair<unsigned int, double>> &Camera::get_rays_buf() const
{
    return rays_buf;
}


// взять длинну стороны квадрата
unsigned int Camera::get_side_square_size() const
{
    return side_square_size;
}


// Сеттеры
void Camera::set_position(float new_x, float new_y)
{
    pos = {new_x, new_y};
}

void Camera::set_field_of_view(double angle_in_radians)
{
    fov = angle_in_radians;
    if (angle_in_radians <= 0 || angle_in_radians > 2 * M_PI)
        throw std::logic_error("Camera.field_of_view must be in range  0 < angle <= 2* M_PI\n");
}

void Camera::set_speed(double new_speed)
{
    speed = new_speed;
    if (speed <= 0)
        throw std::logic_error("Camera.speed must be greater than 0\n");
}

void Camera::set_rotation(double angle_in_radians)
{
    rot_a = rc::radians_normalise(angle_in_radians);
}

void Camera::set_n_rays(unsigned int n)
{
    n_rays = n;
}

void Camera::set_visual_range(unsigned int vr)
{
    visual_range = vr;
}

void Camera::set_side_square_size(unsigned int size)
{
    side_square_size = size;
}

void Camera::set_collider()
{
    col = Collider({pos.x - side_square_size / 2, pos.y - side_square_size / 2},
                   {pos.x + side_square_size / 2, pos.y + side_square_size / 2});
}

// Движение игрока
void Camera::move()
{
    sf::Vector2f perpendicular;

    for (auto wall_collider : world.get_colliders())
    {
        if (col.is_collised(wall_collider, speed))
        {
            perpendicular += col.get_collision_perpendicular(wall_collider, speed);
        }
    }

    rot_a = rc::radians_normalise(rot_a);

    double cos_a = cos(rot_a),
            sin_a = sin(rot_a);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        pos.x += speed * cos_a;
        pos.y -= speed * sin_a;

        // проверка на совпадение движения и вектора соприкосновения
        if (perpendicular.x < 0 && cos_a > 0)
        {
            pos.x -= speed * cos_a;
        }
        else if (perpendicular.x > 0 && cos_a < 0)
        {
            pos.x -= speed * cos_a;
        }
        if (perpendicular.y < 0 && sin_a < 0)
        {
            pos.y += speed * sin_a;
        }
        else if (perpendicular.y > 0 && sin_a > 0)
        {
            pos.y += speed * sin_a;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        pos.x += speed * sin_a;
        pos.y += speed * cos_a;

        // проверка на совпадение движения и вектора соприкосновения
        if (perpendicular.x < 0 && sin_a > 0)
        {
            pos.x -= speed * sin_a;
        }
        else if (perpendicular.x > 0 && sin_a < 0)
        {
            pos.x -= speed * sin_a;
        }
        if (perpendicular.y < 0 && cos_a > 0)
        {
            pos.y -= speed * cos_a;
        }
        else if (perpendicular.y > 0 && cos_a < 0)
        {
            pos.y -= speed * cos_a;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        pos.x -= speed * cos_a;
        pos.y += speed * sin_a;

        // проверка на совпадение движения и вектора соприкосновения
        if (perpendicular.x < 0 && cos_a < 0)
        {
            pos.x += speed * cos_a;
        }
        else if (perpendicular.x > 0 && cos_a > 0)
        {
            pos.x += speed * cos_a;
        }
        if (perpendicular.y < 0 && sin_a > 0)
        {
            pos.y -= speed * sin_a;
        }
        else if (perpendicular.y > 0 && sin_a < 0)
        {
            pos.y -= speed * sin_a;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        pos.x -= speed * sin_a;
        pos.y -= speed * cos_a;

        // проверка на совпадение движения и вектора соприкосновения
        if (perpendicular.x < 0 && sin_a < 0)
        {
            pos.x += speed * sin_a;
        }
        else if (perpendicular.x > 0 && sin_a > 0)
        {
            pos.x += speed * sin_a;
        }
        if (perpendicular.y < 0 && cos_a < 0)
        {
            pos.y += speed * cos_a;
        }
        else if (perpendicular.y > 0 && cos_a > 0)
        {
            pos.y += speed * cos_a;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        rot_a -= 0.01;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        rot_a += 0.01;

    // установка колайдера
    set_collider();
}

void Camera::rendering_3d(sf::RenderWindow &win)
{
    rays_buf = rc::ray_casting(world.get_walls_coords(), world.get_tile_size(), rc::Coords{pos.x, pos.y}, rot_a, visual_range, fov, n_rays);

    const unsigned int raysSize = rays_buf.size();
    const sf::Vector2u windowSize = win.getSize();

    float dist_to_scrn = raysSize / (2 * std::tan(fov / 2));
    float projection_coeff = windowSize.y * (dist_to_scrn * world.get_tile_size()) / n_rays;
    float scale = static_cast<float>(windowSize.x) / raysSize;

    sf::Uint8 color;
    float projection_wall_height;
    for (unsigned int i = 0; i < raysSize; ++i)
    {
        auto ray = rays_buf[i];
        if (ray.first == visual_range) continue; // если объекта не встретилось, не выполнять расчеты и не отрисовывать несуществующий объект на расстоянии visual_range

        ray.first *= cos(rot_a - ray.second);

        projection_wall_height = projection_coeff / ray.first;

        color = static_cast<sf::Uint8>(255 / (1 + ray.first * 0.004));

        sf::RectangleShape r{sf::Vector2f{(float)scale, projection_wall_height}};
        r.setPosition({i * static_cast<float>(scale), windowSize.y / 2 - projection_wall_height / 2});
        r.setFillColor(sf::Color{color, color, color});

        win.draw(r);
    }
}


static void draw_camera(sf::RenderWindow& w,const rc::Coords& cmr)
{
    sf::CircleShape c{15};
    c.setPosition({cmr.x - 15,cmr.y - 15});
    c.setFillColor(sf::Color::Blue);
    w.draw(c);
}



void Camera::draw_line(sf::RenderWindow& w,rc::Coords cmr, int dist, sf::Vector2f min_border, sf::Vector2f max_border, double rot_angle, sf::Color color,double multiply)
{
    rot_angle = rc::radians_normalise(rot_angle);

    dist *=multiply;

    if(cmr.x + dist * cos(rot_angle)>max_border.x)
    {
        dist = (max_border.x-cmr.x)/cos(rot_angle);
    }
    else if(cmr.x + dist * cos(rot_angle) < min_border.x)
    {
        dist = (min_border.x-cmr.x)/cos(rot_angle);
    }
    if(cmr.y - dist * sin(rot_angle)>max_border.y)
    {
        dist = -(max_border.y-cmr.y)/sin(rot_angle);
    }
    else if(cmr.y - dist * sin(rot_angle) < min_border.y)
    {
        dist = -(min_border.y-cmr.y)/sin(rot_angle);
    }

    sf::VertexArray line{ sf::Lines, 2 };

    line[0] = sf::Vector2f{cmr.x, cmr.y};
    line[1] = sf::Vector2f{cmr.x + dist * cos(rot_angle), cmr.y - dist * sin(rot_angle)};
    line[0].color = color;
    line[1].color = color;
    w.draw(line);
}

void Camera::rendering_2d(sf::RenderWindow &win)
{
    rays_buf = rc::ray_casting(world.get_walls_coords(), world.get_tile_size(), rc::Coords{pos.x, pos.y},rot_a, visual_range, fov, n_rays);
    for (auto ray: rays_buf)
        draw_line(win,{pos.x, pos.y}, ray.first,{0,0},{win.getSize().x,win.getSize().y}, ray.second, sf::Color::White,1);
    draw_camera(win,{pos.x, pos.y}); // Отрисовка Камеры
}

void Camera::draw(sf::RenderWindow &win, Rendering_Mode mode)
{
    if (mode == Rendering_Mode::M_3D)
        rendering_3d(win);
    else if (mode == Rendering_Mode::M_2D)
        rendering_2d(win);
}
