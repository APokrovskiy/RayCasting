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
    "001000000000000",
    "100000000000000",
    "100000010000000",
    "000000000000000",
    "001000000000000",
    "100000000000000",
    "000000000000000",
    "000000000000000"
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
    distance res = (pl.first / TILE + 1) * TILE - pl.first;
    rot_angle = radians_normalise(rot_angle);

    if (rot_angle == 0) /* RIGHT */
    {       
        while ( (res < vis_range) && !(world_map.find(Coords{(pl.first + res) / TILE, pl.second / TILE}) != world_map.end()) )
        {
            res += TILE;
        }
        if ( res >= vis_range )
        {
            return -1;
        }
        return res;
    }
    else if (rot_angle == M_PI) /* LEFT */
    {
        res = TILE - res;
        while ( (res < vis_range) && !(world_map.find(Coords{(pl.first - res) / TILE, pl.second / TILE}) != world_map.end()) )
        {
            res += TILE;
        }
        if ( res >= vis_range )
        {
            return -1;
        }
        return res - TILE;
    }
    else if (rot_angle == 3 * M_PI / 2) /* DOWN */
    {
        res = (pl.second / TILE + 1) * TILE - pl.second;
        while ( (res < vis_range) && !(world_map.find(Coords{pl.first / TILE, (pl.second + res) / TILE}) != world_map.end()) )
        {
            std::cout << "RAY-COORDS: (" << pl.first / TILE << ";" << (pl.second + res) / TILE << ")\n";
            res += TILE;
        }
        if ( res >= vis_range )
        {
            std::cout << "res =  " << res << '\n'; 
            return -1;
        }
        return res;
    }
    else if (rot_angle == M_PI / 2) /* UP */
    {
        res = (pl.second / TILE + 1) * TILE - pl.second;
        res = TILE - res;
        while ( (res < vis_range) && !(world_map.find(Coords{pl.first / TILE, (pl.second - res) / TILE}) != world_map.end()) )
        {
            res += TILE;
        }
        if ( res >= vis_range )
        {
            return -1;
        }
        return res - TILE;
    }
}


int main()
{
    Coords player = {250, 250};
    World_Map wm = init_world_map(text_map);
    for (Coords crd: wm)
    {
        std::cout << "WALL: (" << crd.first << ";" << crd.second << ")\n";
    }
    distance d = raycast(wm, player, M_PI * 3 / 2 , 200000);
    std::cout << d;
    std::cin.get();
    return 0;
}
