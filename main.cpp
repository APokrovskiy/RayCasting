#include <iostream>
#include <vector>
#include <string>
#include <set>

typedef int distance;
typedef std::pair<int, int> Coords;
typedef std::set< Coords > World_Map;

enum class Direction
{
    RIGHT,
    LEFT,
    UP,
    DOWN
};

std::vector<std::string> text_map = 
{
    "000000000000000",
    "100000000000000",
    "100000010000000",
    "000000000000000",
    "000000000000000",
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

distance raycast(World_Map world_map, Coords pl, Direction dir, distance vis_range)
{
    distance res = (pl.first / TILE + 1) * TILE - pl.first;
    if (dir == Direction::RIGHT)
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
    else if (dir == Direction::LEFT)
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
    else if (dir == Direction::DOWN)
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
    else if (dir == Direction::UP)
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
    distance d = raycast(wm, player, Direction::LEFT, 200000);
    std::cout << d;
    std::cin.get();
    return 0;
}
