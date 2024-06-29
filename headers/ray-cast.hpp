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

    double radians_normalise(double angle_in_radians);

    std::set< rc::Coords > init_world_map(std::vector<std::string>& text_map, char wall_character);

    unsigned int ray_cast(const std::set<rc::Coords>& world_map, int cell_size, rc::Coords camera, double rotation_angle, unsigned int visual_range);
    
    std::vector<std::pair<unsigned int, double>> ray_casting(const std::set<rc::Coords>& world_map, int cell_size, rc::Coords camera,double rotation_angle, unsigned int visual_range, double fov, int n_rays);

}