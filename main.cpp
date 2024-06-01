#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <windows.h>

typedef int distance;
typedef std::pair<int, int> Coords;
typedef std::set< Coords > World_Map;

#define dbgvar(VAR_NAME) #VAR_NAME " = " << VAR_NAME

std::vector<std::string> text_map = 
{
    "0000000000",
    "0110001110",
    "0110001110",
    "0000000000",
    "0011100010",
    "0010001110",
    "0000000000"
};
const int TILE = 100;

World_Map init_world_map(std::vector<std::string>& text_map)
{
    World_Map res;
    for (int y = 0; y < text_map.size(); y++)
        for (int x = 0; x < text_map[y].size(); x++)
        {
            if (text_map[y][x] == '1')
            {
                res.emplace(x, y);
            }
        }

    return res;
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


// TODO Поменять структуру карты на обычный массив строк
distance raycast(World_Map world_map, Coords pl, double rot_angle, distance vis_range)
{   
    rot_angle = radians_normalise(rot_angle);

    int va, vb, ha, hb;
    double BAC, EAD;
    bool  vray_is_completed = false, hray_is_completed = false;
    Coords vintersection, hintersection;
    // TODO: Найти закономерность
    // Определение углов треугольника
    if (rot_angle >= 0 && rot_angle <= M_PI_2)
    {
        BAC = rot_angle;
        EAD = M_PI_2 - rot_angle;
    }
    else if ( rot_angle >= M_PI_2 && rot_angle <= M_PI)
    {
        BAC = M_PI - rot_angle;
        EAD = M_PI_2 - BAC;
    }
    else if (rot_angle >= M_PI && rot_angle <= 3 * M_PI / 2)
    {
        BAC = rot_angle - M_PI;
        EAD = 3* M_PI / 2 - rot_angle;
    }
    else if (rot_angle >= 3 * M_PI_2 )
    {
        BAC = 2 * M_PI - rot_angle;
        EAD = M_PI_2 - (2 * M_PI - rot_angle);
    }

    // Определение катетов
    va = (pl.first/TILE + 1) * TILE - pl.first; // Если (x > 0) на тригонометрической окружности
    if ( rot_angle >= M_PI_2 && rot_angle <= 3 * M_PI_2) // Если же (x < 0) на тригонометрической окружности
        va = TILE - va;
    
    ha = (pl.second /TILE + 1)* TILE - pl.second; // Если (y < 0) на тригонометрической окружности
    if (rot_angle >= 0 && rot_angle <=  M_PI) // Если же (y > 0) на тригонометрической окружности
        ha = TILE - ha;

    vb = va * tan(BAC);
    hb = ha * tan(EAD);


    while (true)
    {
        if (std::isnan(sqrt(va * va + vb * vb)))
            vray_is_completed = true;
        if (std::isnan(sqrt(ha * ha + hb * hb)))
            hray_is_completed = true;

        //Определение потенциальных точек пересечения
        if (rot_angle >= 0 && rot_angle <= M_PI_2)
        {
            vintersection = {(pl.first + va)/TILE, (pl.second - vb)/TILE};
            hintersection = {(pl.first + hb)/TILE, (pl.second - ha)/TILE - 1};
        }
        else if ( rot_angle >= M_PI_2 && rot_angle <= M_PI)
        {
            vintersection = {(pl.first - va)/TILE - 1, (pl.second - vb)/TILE};
            hintersection = {(pl.first - hb)/ TILE, (pl.second - ha)/TILE - 1};
        }
        else if (rot_angle >= M_PI && rot_angle <= 3 * M_PI / 2)
        {
            vintersection = {(pl.first - va)/TILE - 1, (pl.second + vb)/TILE};
            hintersection = {(pl.first - hb)/TILE, (pl.second + ha)/TILE};
        }
        else if (rot_angle >= 3 * M_PI_2 )
        {
            vintersection = {(pl.first + va)/TILE,(pl.second + vb)/TILE}; 
            hintersection = {(pl.first + hb)/TILE, (pl.second + ha)/TILE};
        }
        
        if ((hb >= va || ha >= vb) || hray_is_completed)
            {
                
                if (!vray_is_completed && (sqrt(va * va + vb * vb) < vis_range) && !(world_map.find(vintersection) != world_map.end()) )
                {
                    va += TILE;
                    vb = va * tan(BAC);
                }
                else if (sqrt(va * va + vb * vb) >= vis_range)
                    vray_is_completed = true;
                else if (world_map.find(vintersection) != world_map.end())
                    return sqrt(va * va + vb * vb);
            }
            
            if ((!(hb >= va || ha >= vb)) || vray_is_completed)
            { 
                if (!hray_is_completed && (sqrt(ha * ha + hb * hb) < vis_range) && !(world_map.find(hintersection) != world_map.end()) )
                {
                    ha += TILE;
                    hb = ha * tan(EAD);
                } 
                else if (sqrt(ha * ha + hb * hb) >= vis_range)
                    hray_is_completed = true;
                else if (world_map.find(hintersection) != world_map.end())
                    return sqrt(ha * ha + hb * hb);
            }
            
            if (vray_is_completed && hray_is_completed)
                return vis_range;
    }
}


// Функции для отрисовки объектов
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_world_map(sf::RenderWindow& w, World_Map& m)
{
    for (Coords crd: m)
    {
        sf::RectangleShape r{{TILE, TILE}};
        r.setPosition({crd.first * TILE,crd.second * TILE});
        w.draw(r);
    }
}
void draw_player(sf::RenderWindow& w,Coords& pl)
{
    sf::CircleShape c{15};
    c.setPosition({pl.first - 15,pl.second - 15});
    c.setFillColor(sf::Color::Blue);
    w.draw(c);
}
void draw_line(sf::RenderWindow& w,Coords pl, distance dist, double rot_angle)
{
    rot_angle = radians_normalise(rot_angle);
    sf::VertexArray line{ sf::Lines, 2 };
    line[0] = sf::Vector2f{pl.first, pl.second};
    line[1] = sf::Vector2f{pl.first + dist * cos(rot_angle), pl.second - dist * sin(rot_angle) };
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;
    w.draw(line);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    sf::RenderWindow window{sf::VideoMode{1920, 1080},"Ray"};
    window.setFramerateLimit(60);
    std::cout << "Start Game...\n";
    std::cout << "-----------------------------\n";
    Coords player = {450, 350};
    std::cout << "Player init.\nPlayer Coords: (" << player.first << ';' << player.second << ")\nPlayer's TILE: (" <<  player.first / TILE << ';' << player.second / TILE << ")\n";
    std::cout << "-----------------------------\n";
    World_Map wm = init_world_map(text_map);
    std::cout << "Map init.\n";
    for (Coords crd: wm)
    {
        std::cout << "WALL: (" << crd.first << ";" << crd.second << ")\n";
    }


    double angle = 0;



    


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
            player.second -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.first -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.second += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.first += 1;
        

        window.clear();

        

        distance d = raycast(wm,player, angle,5000);
        draw_world_map(window, wm);
        draw_player(window,player);
        draw_line(window,player, d, angle);
        
        window.display();
    }


    

    std::cin.get();
    return 0;
}