#pragma once

#include <set>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ray-cast.hpp"
#include "Collider.hpp"
#include "Settings_Updater.hpp"

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
    void draw_map(sf::RenderWindow& win,float multiply,float map_size,sf::Vector2f pos);


private:
    World_Map wm;
    unsigned int tile;

    std::vector<Collider> wall_colliders;

    void draw_background(sf::RenderWindow& win,float map_size,float tile_on_map);
    void draw_out_line_background(sf::RenderWindow& win,float map_size,float tile_on_map);
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