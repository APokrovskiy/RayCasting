#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>

typedef int distance;
typedef std::pair<int, int> Coords;
typedef std::set< Coords > World_Map;

std::vector<std::string> text_map = 
{
    "0000100000",
    "0000000000",
    "0000000000",
    "0100000001",
    "0000000000",
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


int main()
{
    std::cout << "Start Game...\n";
    Coords player = {460, 330};
    std::cout << "Player init.\nPlayer Coords: (" << player.first << ';' << player.second << ")\nPlayer's TILE: (" <<  player.first / TILE << ';' << player.second / TILE << ")\n";
    World_Map wm = init_world_map(text_map);
    std::cout << "Map init.\n";
    for (Coords crd: wm)
    {
        std::cout << "WALL: (" << crd.first << ";" << crd.second << ")\n";
    }
    std::cout 
        <<"RIGHT: " << raycast(wm, player, 0 , 8 * 100) << '\n'
        <<"UP: " <<  raycast(wm, player, M_PI / 2 , 8 * 100) << '\n'
        <<"LEFT: " <<  raycast(wm, player, M_PI , 8 * 100) << '\n'
        <<"DOWN: " <<  raycast(wm, player, 3 * M_PI / 2 , 8 * 100) << std::endl;

    std::cin.get();
    return 0;
}
