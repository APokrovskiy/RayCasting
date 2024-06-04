#define _USE_MATH_DEFINES

#define dbgvar(VAR) #VAR " = " << VAR
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
    "10011110001101",
    "11011000001101",
    "10011001000001",
    "11000000000001",
    "10001100001001",
    "11001000001001",
    "11111111111111"
};
const int TILE = 100;


double radians_normalise(double angle_in_radians); // 0 <= angle <= 2 * M_PI
// Функции для отрисовки объектов
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_world_map(sf::RenderWindow& w, std::set<rc::Coords>& m);
void draw_player(sf::RenderWindow& w,rc::Coords& pl);
void draw_line(sf::RenderWindow& w,rc::Coords pl, int dist, double rot_angle, sf::Color color = sf::Color::Red);
///////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    sf::RenderWindow window{sf::VideoMode{1920, 1080},"Ray"};
    window.setFramerateLimit(60);

    rc::Coords player = {450, 350};
    std::set<rc::Coords> wm = rc::init_world_map(text_map, '1');


    double angle = 0;


    ///////////////////////////////////////////
    int n_rays = 10000;
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
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            angle += 0.01;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            angle -= 0.01;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.y -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.y += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.x += 1;
        

        window.clear();

        draw_world_map(window, wm);
        draw_player(window,player);
        rays = rc::ray_casting(wm,TILE,player,angle, 5000, M_PI/3, n_rays);
        for (auto p: rays)
        {
            //std::cout << dbgvar(p.first) << ' ' << dbgvar(p.second) << '\n';
            draw_line(window,player, p.first, p.second, sf::Color::White);
        }
        int d = rc::ray_cast(wm,TILE,player, angle,5000);
        draw_line(window,player, d , angle, sf::Color::Blue);
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
void draw_player(sf::RenderWindow& w,rc::Coords& pl)
{
    sf::CircleShape c{15};
    c.setPosition({pl.x - 15,pl.y - 15});
    c.setFillColor(sf::Color::Blue);
    w.draw(c);
}
void draw_line(sf::RenderWindow& w,rc::Coords pl, int dist, double rot_angle, sf::Color color)
{
    rot_angle = radians_normalise(rot_angle);
    sf::VertexArray line{ sf::Lines, 2 };
    line[0] = sf::Vector2f{pl.x, pl.y};
    line[1] = sf::Vector2f{pl.x + dist * cos(rot_angle), pl.y - dist * sin(rot_angle) };
    line[0].color = color;
    line[1].color = color;
    w.draw(line);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
