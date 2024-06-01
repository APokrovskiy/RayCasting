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
    "11111111111111111111111",
    "11100011100001111000001",
    "11100011100000001000001",
    "10000000000010001000001",
    "10111000100011100000001",
    "10100011100011100000001",
    "10100011100000100000111",
    "10100000000000000000001",
    "10100011100001000100001",
    "10111111100000011111001",
    "11111111111111111111111"
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
    // 0 <= rot_angle <= 2 * M_PI
    rot_angle = radians_normalise(rot_angle);

    // Использованные переменные
    //////////////////////////////////////////////////////////////
    int va, vb, ha, hb;                                         // Катеты треугольников
    double BAC, EAD;                                            // Углы треугольников
    Coords vintersection, hintersection, vcell, hcell;          // Координаты пересечения и ячейки, с которыми лучи пересекаются
    bool  vray_is_completed = false, hray_is_completed = false; // Луч перестал искать пересечения по вертикальным/горизонтальным линиям?
    //////////////////////////////////////////////////////////////

    // Определение углов треугольников
    ///////////////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////////////


    // Определение катетов треугольников
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    va = (pl.first/TILE + 1) * TILE - pl.first; // Если (x > 0) на тригонометрической окружности
    if ( rot_angle >= M_PI_2 && rot_angle <= 3 * M_PI_2) // Если (x < 0) на тригонометрической окружности
        va = TILE - va;
    
    ha = (pl.second /TILE + 1)* TILE - pl.second; // Если (y < 0) на тригонометрической окружности
    if (rot_angle >= 0 && rot_angle <=  M_PI) // Если (y > 0) на тригонометрической окружности
        ha = TILE - ha;

    vb = va * tan(BAC);
    hb = ha * tan(EAD);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (true)
    {
        // Если происходит переполнение, при расчете расстояния
        ////////////////////////////////////////////////////
        if (std::isnan(sqrt(va * va + vb * vb)))
            vray_is_completed = true;
        if (std::isnan(sqrt(ha * ha + hb * hb)))
            hray_is_completed = true;
        ////////////////////////////////////////////////////

        // Определение потенциальных координат пересечения
        ////////////////////////////////////////////////////////////////
        if (rot_angle >= 0 && rot_angle <= M_PI_2)
        {
            vintersection = {(pl.first + va), (pl.second - vb)};
            hintersection = {(pl.first + hb), (pl.second - ha) - TILE};
        }
        else if ( rot_angle >= M_PI_2 && rot_angle <= M_PI)
        {
            vintersection = {(pl.first - va) - TILE, (pl.second - vb)};
            hintersection = {(pl.first - hb), (pl.second - ha) - TILE};
        }
        else if (rot_angle >= M_PI && rot_angle <= 3 * M_PI / 2)
        {
            vintersection = {(pl.first - va) - TILE, (pl.second + vb)};
            hintersection = {(pl.first - hb), (pl.second + ha)};
        }
        else if (rot_angle >= 3 * M_PI_2 )
        {
            vintersection = {(pl.first + va),(pl.second + vb)}; 
            hintersection = {(pl.first + hb), (pl.second + ha)};
        }  
        ////////////////////////////////////////////////////////////////

        // Определение ячеек, с которыми пересекаются лучи 
        //////////////////////////////////////////////////////////////////
        vcell = {vintersection.first / TILE, vintersection.second / TILE};
        hcell = {hintersection.first / TILE, hintersection.second / TILE};
        //////////////////////////////////////////////////////////////////
        
        // Поиск пересечения по вертикальным линиям
        if ((hb >= va || ha >= vb) || hray_is_completed)
        {
            if ( (vintersection.first % TILE == 0) && (vintersection.second % TILE == 0 )) // Если луч находится в точке пересечения 4 ячеек карты
            {
                if  ( 
                        (world_map.find({vcell.first - 1, vcell.second}) != world_map.end())     || 
                        (world_map.find({vcell.first - 1, vcell.second - 1}) != world_map.end()) ||
                        (world_map.find({vcell.first, vcell.second - 1}) != world_map.end()) 
                    )
                    return sqrt(va * va + vb * vb);
            }

            if (!vray_is_completed && (sqrt(va * va + vb * vb) < vis_range) && !(world_map.find(vcell) != world_map.end()) ) // Если стены нет
            {
                va += TILE;
                vb = va * tan(BAC);
            }
            else if (sqrt(va * va + vb * vb) >= vis_range) // Длина луча >= Дальности видимости
                vray_is_completed = true;
            else if (world_map.find(vcell) != world_map.end()) // Если стена есть
                return sqrt(va * va + vb * vb);
        }

        // Поиск пересечения по горизонтальным линиям
        if ((!(hb >= va || ha >= vb)) || vray_is_completed)
        { 
            if ( (hintersection.first % TILE == 0) && (hintersection.second % TILE == 0 )) // Если луч находится в точке пересечения 4 ячеек карты
            {
                if  ( 
                        (world_map.find({hcell.first - 1, hcell.second}) != world_map.end())     ||
                        (world_map.find({hcell.first - 1, hcell.second - 1}) != world_map.end()) || 
                        (world_map.find({hcell.first, hcell.second - 1}) != world_map.end()) 
                    )
                    return sqrt(ha * ha + hb * hb);
            }

            if (!hray_is_completed && (sqrt(ha * ha + hb * hb) < vis_range) && !(world_map.find(hcell) != world_map.end()) ) // Если стены нет
            {
                ha += TILE;
                hb = ha * tan(EAD);
            } 
            else if (sqrt(ha * ha + hb * hb) >= vis_range) // Длина луча >= Дальности видимости
                hray_is_completed = true;
            else if (world_map.find(hcell) != world_map.end()) // Если стена есть
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