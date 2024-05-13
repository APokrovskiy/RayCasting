#include <iostream>
#include <string>
#include <set>

typedef int distance;
typedef int Point;
typedef std::set<Point> World_Map;

enum class Direction
{
    RIGHT,
    LEFT
};

std::string text_map = "000000000001000";
const int TILE = 100;

World_Map init_world_map(std::string text_map)
{
    World_Map res;

    for (int x = 0; x < text_map.size(); x++)
    {
        if (text_map[x] == '1')
        {
            res.emplace(x);
        }
    }

    return res;
}

distance raycasting(World_Map world_map, Point pl, Direction dir, distance vis_range)
{
    distance res = (pl / TILE + 1) * TILE - pl;
    if (dir == Direction::RIGHT)
    {       
        while ( (res < vis_range) && !(world_map.find((pl + res) / TILE) != world_map.end()) )
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
        while ( (res < vis_range) && !(world_map.find((pl - res) / TILE) != world_map.end()) )
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
    Point player = 97;
    World_Map wm = init_world_map(text_map);
    distance d = raycasting(wm, player, Direction::RIGHT, 200000);
    std::cout << d;
    std::cin.get();
    return 0;
}
