#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <set>

#include <SFML/Graphics.hpp>

#include "Collider.hpp"
#include "ray-cast.hpp"
#include "World.hpp"


class Camera
{
public:
    explicit Camera(World& wrld, int size);

    enum class Rendering_Mode {M_2D, M_3D};

    // Геттеры
    // TODO: Сделать встраиваемыми
    sf::Vector2f get_position() const;
    double get_rotation() const;
    double get_speed() const;
    unsigned int get_n_rays() const;
    const std::vector<std::pair<unsigned int, double>>& get_rays_buf() const;
    unsigned int get_side_square_size() const;

    //Сеттеры
    void set_position(float new_x, float new_y);
    void set_field_of_view(double angle_in_radians);
    void set_speed(double new_speed);
    void set_rotation(double angle_in_radians);
    void set_n_rays(unsigned int);
    void set_visual_range(unsigned int);
    void set_side_square_size(unsigned int);
    void set_collider();

    // Движение игрока
    void move();

    // Рендеринг изображения
    void draw(sf::RenderWindow& win, Rendering_Mode mode);

private:
    // Положение камеры в пространстве
    sf::Vector2f pos{0,0}; 
    double speed{1}; 
    double rot_a{M_PI / 3}; 

    // Настройки рендеринга
    unsigned int n_rays{100};
    unsigned int visual_range{2000};
    double fov{M_PI/3};
    std::vector<std::pair<unsigned int, double>> rays_buf;

    //Настройка колизии
    unsigned int side_square_size;
    Collider col{{0,0},{0,0}}; // TODO: Сделать круг на 2d карте был диаметром равным стороны col

    // Указатель на мир
    World& world;

    void rendering_3d(sf::RenderWindow& win);
    void rendering_2d(sf::RenderWindow& win);
};