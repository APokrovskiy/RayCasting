#include "Settings_Updater.hpp"

#include <string>
#include "Observer/JSON_File_Observer.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Background.hpp"
#include "Button.hpp"

Settings_Updater::Settings_Updater(const std::string &path_to_settings_file) : observer(path_to_settings_file)
{
    settings = observer.update_settings(load_settings);
}

bool Settings_Updater::is_file_changed()
{
    return observer.is_file_changed();
}

// TODO: Убрать все лишние повторения настроек
void Settings_Updater::update(sf::RenderWindow &window, World &world, Camera &cmr, Background &background, Button &menu_button)
{

    settings = observer.update_settings(load_settings);

    window.setFramerateLimit(settings.win.fps_limit);

    world = World{settings.world.string_map, settings.world.wall_char, settings.world.tile_size};

    if (pos != sf::Vector2f{settings.cmr.cmr_pos_x, settings.cmr.cmr_pos_y})
    {
        cmr.set_position(settings.cmr.cmr_pos_x, settings.cmr.cmr_pos_y);
        pos = cmr.get_position();
    }

    cmr.set_field_of_view(settings.cmr.fov);

    if (rot_a != settings.cmr.rot_a)
    {
        rot_a = settings.cmr.rot_a;
        cmr.set_rotation(rot_a);
    }

    cmr.set_speed(settings.cmr.speed);

    cmr.set_n_rays(settings.cmr.n_rays);

    cmr.set_visual_range(settings.cmr.vis_r);
}
