#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <set>

#include <SFML/Graphics.hpp>

#include "ray-cast.hpp"
#include "World.hpp"


class Camera
{
public:
    explicit Camera(World& wrld);

    enum class Rendering_Mode {M_2D, M_3D};

    // Геттеры
    inline sf::Vector2f get_position() const;
    inline double get_rotation() const;
    inline double get_speed() const;
    inline unsigned int get_n_rays() const;
    inline const std::vector<std::pair<unsigned int, double>>& get_rays_buf() const;

    //Сеттеры
    void set_position(float new_x, float new_y);
    void set_field_of_view(double angle_in_radians);
    void set_speed(double new_speed);
    void set_rotation(double angle_in_radians);
    void set_n_rays(unsigned int);
    void set_visual_range(unsigned int);
    

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

    // Указатель на мир
    World& world;

    void rendering_3d(sf::RenderWindow& win);
    void rendering_2d(sf::RenderWindow& win);
};