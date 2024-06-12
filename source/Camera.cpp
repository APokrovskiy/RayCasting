#include "Camera.hpp"

#include <cmath>
#include <exception>

Camera::Camera(World& w): world(w){}



 // Геттеры
inline sf::Vector2f Camera::get_position() const
{
    return pos;
}

inline double Camera::get_rotation() const
{
    return rot_a;
}

inline int Camera::get_speed() const
{
    return speed;
}

inline unsigned int Camera::get_n_rays() const
{
    return n_rays;
}

inline const std::vector<std::pair<unsigned int, double>>& Camera::get_rays_buf() const
{
    return rays_buf;
}

//Сеттеры
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


void Camera::set_speed(int new_speed)
{
    speed = new_speed;
    if (speed <= 0)
    {
        throw std::logic_error("Camera.speed must be greater than 0\n");
    }
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

// Движение игрока
void Camera::move() 
{
    rot_a = rc::radians_normalise(rot_a);
    double cos_a = cos(rot_a),
            sin_a = sin(rot_a);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        pos.x += speed * cos_a;
        pos.y -= speed * sin_a;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
    {
        pos.x -= speed * cos_a;
        pos.y += speed * sin_a;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rot_a -= 0.01;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
        rot_a += 0.01; 
}

void Camera::rendering_3d(sf::RenderWindow& win)
{
    rays_buf = rc::ray_casting(world.get_walls_coords(), world.get_tile_size(), rc::Coords{pos.x, pos.y},rot_a, visual_range, fov, n_rays);

    const unsigned int raysSize = rays_buf.size();
    const sf::Vector2u windowSize = win.getSize();

    float dist_to_scrn = raysSize / (2 * std::tan(fov / 2));
    float projection_coeff = 3 * dist_to_scrn * world.get_tile_size();
    float scale = static_cast<float>(windowSize.x) / raysSize;


    for (unsigned int i = 0; i < raysSize; ++i) 
    {
        const auto& ray = rays_buf[i];
        if (ray.first == visual_range) continue; // если объекта не встретилось, не выполнять расчеты и не отрисовывать несуществующий объект на расстоянии visual_range

        float projection_wall_height = projection_coeff / ray.first;
        
        sf::Uint8 r_color = static_cast<sf::Uint8>(255 / (1 + ray.first * 0.004));//TODO: Убрать инициализацию в цикле
        
        sf::RectangleShape r{ sf::Vector2f{(float)scale, projection_wall_height} }; //TODO: Убрать инициализацию в цикле
        r.setPosition({ i * static_cast<float>(scale), windowSize.y / 2 - projection_wall_height / 2 });
        r.setFillColor(sf::Color{ r_color, r_color, r_color });
        
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
static void draw_line(sf::RenderWindow& w,rc::Coords cmr, int dist, double rot_angle, sf::Color color)
{
    rot_angle = rc::radians_normalise(rot_angle);
    sf::VertexArray line{ sf::Lines, 2 };
    line[0] = sf::Vector2f{cmr.x, cmr.y};
    line[1] = sf::Vector2f{cmr.x + dist * cos(rot_angle), cmr.y - dist * sin(rot_angle) };
    line[0].color = color;
    line[1].color = color;
    w.draw(line);
}

void Camera::rendering_2d(sf::RenderWindow& win)
{
    rays_buf = rc::ray_casting(world.get_walls_coords(), world.get_tile_size(), rc::Coords{pos.x, pos.y},rot_a, visual_range, fov, n_rays);
    for (auto ray: rays_buf)
        draw_line(win,{pos.x, pos.y}, ray.first, ray.second, sf::Color::White);
    draw_camera(win,{pos.x, pos.y}); // Отрисовка Камеры
}

void Camera::draw(sf::RenderWindow& win, Rendering_Mode mode)
{
    if (mode == Rendering_Mode::M_3D)
        rendering_3d(win);
    else if (mode == Rendering_Mode::M_2D)
        rendering_2d(win);
}

