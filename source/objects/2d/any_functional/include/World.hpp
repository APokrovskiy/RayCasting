#pragma once

#include <set>
#include <vector>
#include <SFML/Graphics.hpp>

#include "algorithms/2d/include/ray-cast.hpp"
#include "objects/2d/phisic/include/Collider.hpp"
#include "algorithms/other/settings_manager/Settings_Updater.hpp"

class World
{
public:
    using World_Map = std::set<rc::Coords>;

    // TODO: Реализовать конструкторы через перемещение
    World(World_Map &wm, unsigned int tile);
    World(std::vector<std::string> wm, char wall, unsigned int tile); // TODO: передавать векторы по ссылке

    const std::vector<Collider> &get_colliders() { return wall_colliders; }
    const World_Map &get_walls_coords() const { return wm; }
    unsigned int get_tile_size() const { return tile; }

    void set_walls_coords(World_Map &wm);
    void set_walls_coords(std::vector<std::string> wm, char wall);
    void set_tile(unsigned int tile);

    void draw(sf::RenderWindow& win) const;

private:
    World_Map wm;
    unsigned int tile;

    std::vector<Collider> wall_colliders;
};

class WorldSettingsUpdater: public IConcreteSettingsUpdater
{
    World &w;
public:
    WorldSettingsUpdater(World& cmr): w(cmr){}

    void settings_update(const ray_casting_settings& s) override
    {
        w = World{s.world_map, '1', 100};
    }
};