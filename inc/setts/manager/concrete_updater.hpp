#pragma once

#include <SFML/Graphics.hpp>

#include "cmr.hpp"
#include "world.hpp"


class CameraSettingsUpdater: public IConcreteSettingsUpdater
{
    Camera &cmr;
    
    sf::Vector2f pos;
public:
    CameraSettingsUpdater(Camera &cmr): cmr(cmr){}

    void settings_update(const ray_casting_settings& settings) override
    {
        if (pos != sf::Vector2f{static_cast<float>(settings.cmr.cmr_pos_x), static_cast<float>(settings.cmr.cmr_pos_y)})
        {
            cmr.set_position(static_cast<float>(settings.cmr.cmr_pos_x), static_cast<float>(settings.cmr.cmr_pos_y));
            pos = cmr.get_position();
        }

        cmr.set_speed(settings.cmr.speed);

        cmr.set_n_rays(settings.cmr.n_rays);

        cmr.set_visual_range(settings.cmr.vis_r);

        cmr.set_rotation_speed(settings.cmr.rot_speed);
    };

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

class WindowSettingsUpdater: public IConcreteSettingsUpdater
{
    sf::RenderWindow& w;
public:
    WindowSettingsUpdater(sf::RenderWindow& win): w(win) {}

    void settings_update(const ray_casting_settings& s) override
    {
        w.setFramerateLimit(s.fps);
    }
};