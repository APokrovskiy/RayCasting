#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>

typedef int distance;
typedef std::pair<int, int> Coords;
typedef std::set< Coords > World_Map;

#define dbgvar(VAR_NAME) #VAR_NAME " = " << VAR_NAME

std::vector<std::string> text_map = 
{
    "0000100000",
    "0000000000",
    "0000000000",
    "0100000001",
    "0000001000",
    "0000100000"
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

distance raycast(World_Map world_map, Coords pl, double rot_angle, distance vis_range)
{
    distance res; // Возвращаемое функцией расстояние
    Coords intersection; // Потенциальная точка пересечения
    int *var_coord = nullptr /* Изменяющееся значение */, sign;

    rot_angle = radians_normalise(rot_angle); //  0 <= rot_angle < 2 * PI

    // Определение первоначальных значений intersection, var_coord, res
    //////////////////////////////////////////////////////////////////////////////////////
    sign = 1; // Предположим мы двигаемся по направлению оси
    if (rot_angle == 0 || rot_angle == M_PI) /* Оcь X */
    {
        /* Предположим rot_angle == RIGHT */
        res = (pl.first / TILE + 1) * TILE - pl.first;
        if (rot_angle == M_PI) /* Если же это не так (LEFT) */
        {
            res = TILE  - res;
            sign = -1; // Значит двигаемся против оси x
        }

        // Потенциальная точка пересечения
        intersection = {(pl.first + sign * res) / TILE, pl.second / TILE};

        // Изменяющееся значение
        var_coord = &intersection.first;
    }
    else if (rot_angle == M_PI / 2 || rot_angle == 3 * M_PI / 2) /*Ось y*/
    {
        /* Предположим rot_angle == DOWN */
        res = (pl.second / TILE + 1) * TILE - pl.second;
        if (rot_angle == M_PI / 2) /* Если же это не так (UP) */
        {
            res = TILE - res; 
            sign = -1; // Значит движемся против оси y
        }
        // Потенциальная точка пересечения
        intersection = {pl.first / TILE, (pl.second + sign * res) / TILE};

        // Изменяющееся значение
        var_coord = &intersection.second;
    }
    else if (rot_angle > 3 * M_PI / 2)
    {
        int va, vb, ha, hb; // Катеты треугольников для поиска горизонтальных и вертикальных пересечений
        double vangle, hangle; // Углы для треугольников
        Coords vintersection, hintersection;

        // Вычесление начальных переменных для вертикальных линий
        vangle = M_PI / 2 - (rot_angle - 3 * M_PI / 2);
        va = (pl.first / TILE + 1) * TILE - pl.first;
        vb = va * tan(vangle);

        // Вычесление начальных переменных для горизонтальных линий
        hangle = rot_angle - 3 * M_PI / 2;
        ha = (pl.second / TILE + 1) * TILE - pl.second;
        hb = ha * tan(hangle);

        // Сначала будем проверять точку на вертикальной линии
        vintersection = {(pl.first + va) / TILE, (pl.second + vb) / TILE};
        
        hintersection = {(pl.first + hb) / TILE, (pl.second + ha) / TILE};
        /*
        std::cout << "-----------------------------\nStart val\n";
        std::cout << dbgvar(va) << '\n'
                    << dbgvar(vb) << '\n'
                    << dbgvar(vangle) << '\n'
                    << dbgvar(ha) << '\n'
                    << dbgvar(hb) << '\n'
                    << dbgvar(hangle) << '\n'
                    << dbgvar(vintersection.first) << '\n'
                    << dbgvar(vintersection.second) << '\n'
                    << dbgvar(hintersection.first) << '\n'
                    << dbgvar(hintersection.second) << '\n';
        */
        while (true)
        {
            if ( (sqrt(va * va + vb * vb) < vis_range) && !(world_map.find(vintersection) != world_map.end()) )
            {
                va += TILE;
                vb += TILE;
                vintersection = {(pl.first + va) / TILE, (pl.second + vb) / TILE};
            }
            else if (sqrt(va * va + vb * vb) >= vis_range)
                return vis_range;
            else if (world_map.find(vintersection) != world_map.end())
                return sqrt(va * va + vb * vb);
            
            if ((sqrt(ha * ha + hb * hb) < vis_range) && !(world_map.find(hintersection) != world_map.end()))
            {
                ha += TILE;
                hb += TILE;
                hintersection = {(pl.first + hb) / TILE, (pl.second + ha) / TILE};
            }
            else if (sqrt(ha * ha + hb * hb) >= vis_range)
                return vis_range;
            else if (world_map.find(hintersection) != world_map.end())
                return sqrt(ha * ha + hb * hb);
            /*
            std::cout << dbgvar(va) << '\n'
                    << dbgvar(vb) << '\n'
                    << dbgvar(vangle) << '\n'
                    << dbgvar(ha) << '\n'
                    << dbgvar(hb) << '\n'
                    << dbgvar(hangle) << '\n'
                    << dbgvar(vintersection.first) << '\n'
                    << dbgvar(vintersection.second) << '\n'
                    << dbgvar(hintersection.first) << '\n'
                    << dbgvar(hintersection.second) << '\n';
            */

        }

        while ( (sqrt(va * va + vb * vb) < vis_range) && !(world_map.find(intersection) != world_map.end()) )
        {
            va += TILE;
            vb += TILE;
            intersection = {(pl.first + hb) / TILE, (pl.second + ha) / TILE};
            /*
            std::cout << "-----------------------------\n";
                        std::cout << dbgvar(va) << '\n'
                    << dbgvar(vb) << '\n'
                    << dbgvar(vangle) << '\n'
                    << dbgvar(ha) << '\n'
                    << dbgvar(hb) << '\n'
                    << dbgvar(hangle) << '\n'
                    << dbgvar(vintersection.first) << '\n'
                    << dbgvar(vintersection.second) << '\n'
                    << dbgvar(hintersection.first) << '\n'
                    << dbgvar(hintersection.second) << '\n';
            */
            if ((sqrt(ha * ha + hb * hb) < vis_range) && !(world_map.find(intersection) != world_map.end()))
                return sqrt(ha * ha + hb * hb);
            ha += TILE;
            hb += TILE;
            intersection = {(pl.first + va) / TILE, (pl.second + vb) / TILE};
            /*
            std::cout << "-----------------------------\n";
            std::cout << dbgvar(va) << '\n'
                    << dbgvar(vb) << '\n'
                    << dbgvar(vangle) << '\n'
                    << dbgvar(ha) << '\n'
                    << dbgvar(hb) << '\n'
                    << dbgvar(hangle) << '\n'
                    << dbgvar(vintersection.first) << '\n'
                    << dbgvar(vintersection.second) << '\n'
                    << dbgvar(hintersection.first) << '\n'
                    << dbgvar(hintersection.second) << '\n';
            */
        }
        if (sqrt(va * va + vb * vb) >= vis_range)
            return vis_range;
        return sqrt(va * va + vb * vb);

    }
    //////////////////////////////////////////////////////////////////////////////////////

    /*
    std::cout << "sign = " << sign
             << "\nres = " << res
             << "\nintersection.x = " << intersection.first
             << "\n&intersection.x = " << &intersection.first
             << "\nintersection.y = " << intersection.second
             << "\n&intersection.y = " << &intersection.second
             << "\n*var_coord = " << *var_coord 
            << "\nvar_coord = " << var_coord << std::endl; 
    */

    // Бросание луча
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while ( (res < vis_range) && !(world_map.find(intersection) != world_map.end()) )
        {
            // Прибавляем к расстоянию размер плитки
            res += TILE;

            // Изменяем точку пересечения вследствии изменения res
            if (var_coord == &intersection.second)
                *var_coord = (pl.second + sign * res) / TILE;
            else if (var_coord == &intersection.first)
                *var_coord = (pl.first + sign * res) / TILE;
            /*
            std::cout << "res = " << res 
                << "\nintersection.x = " << intersection.first
                << "\n&intersection.x = " << &intersection.first
                << "\nintersection.y = " << intersection.second
                << "\n&intersection.y = " << &intersection.second << std::endl;
            */
        }
        if ( res >= vis_range ) // Луч не достиг объекта
        {
            return -1;
        }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Возврат результата
    if (sign == -1)
        return res - TILE;
    return res;
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
    std::cout << "Start Game...\n";
    std::cout << "-----------------------------\n";
    Coords player = {460, 330};
    std::cout << "Player init.\nPlayer Coords: (" << player.first << ';' << player.second << ")\nPlayer's TILE: (" <<  player.first / TILE << ';' << player.second / TILE << ")\n";
    std::cout << "-----------------------------\n";
    World_Map wm = init_world_map(text_map);
    std::cout << "Map init.\n";
    for (Coords crd: wm)
    {
        std::cout << "WALL: (" << crd.first << ";" << crd.second << ")\n";
    }


    double angle = 3 * M_PI / 2 + M_PI / 4;



    distance d = raycast(wm,player, angle,5000);

    std::cout << "distance = " << d << '\n';
    draw_world_map(window, wm);
    draw_player(window,player);
    draw_line(window,player, d, angle);
    window.display();


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }


    

    std::cin.get();
    return 0;
}
