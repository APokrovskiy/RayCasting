<<<<<<< HEAD
// Подключение библиотек
#include <set>
#define _USE_MATH_DEFINES
#include <math.h>
#include<SFML/Graphics.hpp>

// Карта мира (Можно изменять)
std::vector<std::string> text_map
{
    "1111111111",
    "1000110001",
    "1010001101",
    "1011100101",
    "1000001101",
    "1001001101",
    "1000001101",
    "1011000001",
    "1000001101",
    "1111111111"
};


const int FPS = 30; 
const int WIDTH = 1550, HEIGHT = 1440;
const int TILE = 100;
const int N_RAYS = 120;
const int VISIBILITY_RANGE = WIDTH;
const double FIELD_OF_VIEW = M_PI / 3;

std::set<std::pair<int, int>> init_world_map(std::vector<std::string> &text_map) {
    std::set<std::pair<int, int>> res;
    for (int y = 0; y < text_map.size(); y++)
        for (int x = 0; x < text_map[y].size(); x++)
            if (text_map[y][x] == '1')
                res.emplace(x, y);
    return res;
}

class Player {
    sf::Vector2f pos; 
    float speed; 
    float rot_angle{}; 
public:
    Player(float x, float y, float speed = 2) : pos(x, y), speed(speed) {}

    sf::Vector2f get_position() { return pos; }
    float get_rotation_angle() { return rot_angle; }

    void move() {
        double cos_a = cos(rot_angle),
               sin_a = sin(rot_angle);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            pos.x += speed * cos_a;
            pos.y += speed * sin_a;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            pos.x += speed * sin_a; 
            pos.y -= speed * cos_a;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pos.x -= speed * cos_a;
            pos.y -= speed * sin_a;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            pos.x -= speed * sin_a;
            pos.y += speed * cos_a;
        }  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            rot_angle -= 0.02; 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            rot_angle += 0.02; 
    }
};

sf::VertexArray create_line(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color color = sf::Color::White) {
    sf::VertexArray line{ sf::Lines, 2 };
    line[0] = start;
    line[1] = end;
    line[0].color = color;
    line[1].color = color;
    return line;
}

class Ray_Caster {
    double field_of_view;
    int    num_rays;
    int    vis_range;

    double scale;
    double delta_angle;
    double dist_to_scrn;
    float  projection_coeff;
public:
    Ray_Caster(double fov, int n_rays, int vis_range)
            :field_of_view(fov), num_rays(n_rays), vis_range(vis_range){
        delta_angle = fov / num_rays;
        dist_to_scrn = num_rays / (2 * std::tan(fov / 2));
        projection_coeff = 5 * dist_to_scrn * TILE;
        scale = (double)WIDTH / n_rays;
    }

    void ray_casting(sf::RenderWindow& win, Player& pl, const std::set<std::pair<int, int>>& world_map) {
        double cur_angle = pl.get_rotation_angle() - field_of_view / 2;
        for (int i = 0; i < num_rays; i++) {
            double sin_a = sin(cur_angle),
                   cos_a = cos(cur_angle);
            for (int depth = 0; depth < vis_range; depth++) {
                double x = pl.get_position().x + depth * cos_a,
                       y = pl.get_position().y + depth * sin_a;
                
                if (std::find(world_map.begin(), world_map.end(), std::pair<int, int>{x / TILE, y / TILE}) != world_map.end()) {
                    depth *= cos(pl.get_rotation_angle() - cur_angle);
                    float projection_wall_height = projection_coeff / depth;
                    sf::Uint8 r_color = 255 / (1 + depth  * 0.004);
                    sf::RectangleShape r{ sf::Vector2f{(float)scale, projection_wall_height} };
                    r.setPosition(sf::Vector2f{  i * (float)scale,HEIGHT/2 - projection_wall_height / 2 });
                    r.setFillColor(sf::Color{ r_color, r_color, r_color });
                    win.draw(r);
                    break;
                }
            }
            cur_angle += delta_angle;
        }
        
    }
};

int main() {
    sf::RenderWindow window{ sf::VideoMode{WIDTH, HEIGHT}, "Ray-Casting" };
    window.setFramerateLimit(FPS);
     
    auto world_map = init_world_map(text_map);
    Player player{ WIDTH / 2,HEIGHT / 2}; 

    Ray_Caster ray_caster{
        FIELD_OF_VIEW,
        N_RAYS,
        VISIBILITY_RANGE
    };
    
    while (window.isOpen()){   
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();

        player.move();
        ray_caster.ray_casting(window, player, world_map);

        window.display();

    }
}
=======
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
    "1111111111111111111111",
    "1000000000000000000001",
    "1000001000000001000001",
    "1000000000000000000001",
    "1000000010000100000001",
    "1000000001111000000001",
    "1000000010000100000001",
    "1000000000000000000001",
    "1000001000000001000001",
    "1000010000000000100001",
    "1111111111111111111111"
};
const int TILE = 100;


double radians_normalise(double angle_in_radians); // 0 <= angle <= 2 * M_PI
// Функции для отрисовки объектов
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_world_map(sf::RenderWindow& w, std::set<rc::Coords>& m);
void draw_camera(sf::RenderWindow& w,const rc::Coords& cmr);
void draw_line(sf::RenderWindow& w,rc::Coords cmr, int dist, double rot_angle, sf::Color color = sf::Color::Red);
void rendering_img(sf::RenderWindow& win, std::vector<std::pair<unsigned int, double>>& rays, double fov);
///////////////////////////////////////////////////////////////////////////////////////////////////////////


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

void rendering_img(sf::RenderWindow& win, std::vector<std::pair<unsigned int, double>>& rays, double fov) 
{
    float dist_to_scrn = rays.size() / (2 * std::tan(fov / 2));
    float projection_coeff = 3 * dist_to_scrn * TILE;
    float scale = static_cast<float>(win.getSize().x) / rays.size();
    
    const unsigned int raysSize = rays.size();
    const sf::Vector2u windowSize = win.getSize();


    for (unsigned int i = 0; i < raysSize; ++i) {
        const auto& ray = rays[i];
        float projection_wall_height = projection_coeff / ray.first;
        
        sf::Uint8 r_color = static_cast<sf::Uint8>(255 / (1 + ray.first * 0.004));
        
        sf::RectangleShape r{ sf::Vector2f{(float)scale, projection_wall_height} };
        r.setPosition({ i * static_cast<float>(scale), windowSize.y / 2 - projection_wall_height / 2 });
        r.setFillColor(sf::Color{ r_color, r_color, r_color });
        
        win.draw(r);
    }
}

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
        rays = rc::ray_casting(wm,TILE,cmrcoords,cmr.get_rotation_angle(), 5000, M_PI/3, n_rays);
        // for (auto p: rays)
        //     draw_line(window,cmrcoords, p.first, p.second, sf::Color::White);
        // int d = rc::ray_cast(wm,TILE,cmrcoords, cmr.get_rotation_angle(),5000);
        // draw_line(window,cmrcoords, d , cmr.get_rotation_angle(), sf::Color::Blue); // Отрисовка направления камеры
        //draw_camera(window,cmrcoords); // Отрисовка Камеры
        rendering_img(window,rays, M_PI/3);
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
>>>>>>> Optimized_Algorithm
