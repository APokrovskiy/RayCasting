#pragma once

#include <set>
#include <vector>
#include <string>

namespace rc
{
    struct Coords
    {
        int x{};
        int y{};

        bool operator==(Coords other);
        bool operator!=(Coords other);
        bool operator<(const Coords& other) const;
        Coords(int x, int y): x(x), y(y){};
        Coords() = default;
    };
    
    std::set< rc::Coords > init_world_map(std::vector<std::string>& text_map, char wall_character);

    unsigned int ray_cast(const std::set<rc::Coords>& world_map, int cell_size, rc::Coords camera, double rotation_angle, unsigned int visual_range);
    
}