#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>

#include "ray-cast/ray-cast.hpp"


std::vector<std::string> text_map = 
{
    "11111111111111",
    "11010101010101",
    "10000011110001",
    "11000000001101",
    "10011110101101",
    "11011000001101",
    "10011001000001",
    "11011001100101",
    "10001100101001",
    "11111000101001",
    "11111111111111"
};
const int TILE = 100;


double radians_normalise(double angle_in_radians); // 0 <= angle <= 2 * M_PI
// Функции для отрисовки объектов
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_world_map(sf::RenderWindow& w, std::set<rc::Coords>& m);
void draw_camera(sf::RenderWindow& w,const rc::Coords& cmr);
void draw_line(sf::RenderWindow& w,rc::Coords cmr, int dist, double rot_angle, sf::Color color = sf::Color::Red);
///////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Camera 
{
    sf::Vector2f pos; 
    int speed; 
    double rot_angle{}; 
public:
    Camera(int x, int y, double speed = 1) : pos(x, y), speed(speed) {}

    sf::Vector2f get_position() const { return pos; }
    double get_rotation_angle() const { return rot_angle; }
    
    void move() {
        double cos_a = cos(rot_angle),
               sin_a = sin(rot_angle);
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
            rot_angle -= 0.01; // Поворот налево
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
            rot_angle += 0.01; // Поворот направо
}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
В SFML (Simple and Fast Multimedia Library) используются координаты типа float, а не int, потому что координаты с плавающей запятой обеспечивают более гладкое и точное позиционирование объектов на экране.
Визуальные объекты, такие как спрайты, текстуры и фигуры, могут быть размещены в любом месте на экране с помощью координат X и Y. Когда используются целочисленные координаты (int), перемещение объектов может ограничиваться шагами на целое количество пикселей. Это может привести к рывкам и неровным движениям объектов.
Использование координат с плавающей запятой (float) позволяет плавно перемещать объекты на экране, так как они могут иметь подпиксельное разрешение, что обеспечивает более гладкую анимацию и плавное позиционирование.
Таким образом, выбор типа float в SFML обусловлен стремлением к более точному и профессиональному отображению графики и анимации на экране.
*/ //TODO: Научить работать Ray-Casting с типом Float
int main()
{
    sf::RenderWindow window{sf::VideoMode{1920, 1080},"Ray"};
    window.setFramerateLimit(144);

    Camera cmr = {450, 350,2};
    std::set<rc::Coords> wm = rc::init_world_map(text_map, '1');


    ///////////////////////////////////////////
    int n_rays = 1000;
    std::vector<std::pair<unsigned int, double>> rays(n_rays);
    ///////////////////////////////////////////
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
        }
        
        cmr.move();

        window.clear();
        rc::Coords cmrcoords = {cmr.get_position().x, cmr.get_position().y};
        //draw_world_map(window, wm); // Отрисовка карты
        rays = rc::ray_casting(wm,TILE,cmrcoords,cmr.get_rotation_angle(), 5000, 2 * M_PI, n_rays);
        for (auto p: rays)
            draw_line(window,cmrcoords, p.first, p.second, sf::Color::White);
        int d = rc::ray_cast(wm,TILE,cmrcoords, cmr.get_rotation_angle(),5000);
        draw_line(window,cmrcoords, d , cmr.get_rotation_angle(), sf::Color::Blue); // Отрисовка направления камеры
        //draw_camera(window,cmrcoords); // Отрисовка Камеры
        window.display();
    }

    std::cin.get();
    return 0;
}


double radians_normalise(double angle_in_radians)
{
    while(angle_in_radians >= 2 * M_PI)
    {
        angle_in_radians -= 2 * M_PI;
    }
    while (angle_in_radians < 0)
    {
        angle_in_radians += 2 * M_PI;
    }

    return angle_in_radians;
}



// Функции для отрисовки объектов
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_world_map(sf::RenderWindow& w, std::set<rc::Coords>& m)
{
    for (rc::Coords crd: m)
    {
        sf::RectangleShape r{{TILE, TILE}};
        r.setPosition({crd.x * TILE,crd.y * TILE});
        r.setFillColor(sf::Color::Cyan);
        w.draw(r);
    }
}
void draw_camera(sf::RenderWindow& w,const rc::Coords& cmr)
{
    sf::CircleShape c{15};
    c.setPosition({cmr.x - 15,cmr.y - 15});
    c.setFillColor(sf::Color::Blue);
    w.draw(c);
}
void draw_line(sf::RenderWindow& w,rc::Coords cmr, int dist, double rot_angle, sf::Color color)
{
    rot_angle = radians_normalise(rot_angle);
    sf::VertexArray line{ sf::Lines, 2 };
    line[0] = sf::Vector2f{cmr.x, cmr.y};
    line[1] = sf::Vector2f{cmr.x + dist * cos(rot_angle), cmr.y - dist * sin(rot_angle) };
    line[0].color = color;
    line[1].color = color;
    w.draw(line);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
