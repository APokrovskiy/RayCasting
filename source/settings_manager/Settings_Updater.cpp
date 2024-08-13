#include "Settings_Updater.hpp"



// Settings_Updater::Settings_Updater(const std::string &path_to_settings_file) : observer(path_to_settings_file)
// {
//     settings = observer.update_settings(load_settings);
// }

// bool Settings_Updater::is_file_changed()
// {
//     return observer.is_file_changed();
// }



void Settings_Updater::update(const ray_casting_settings& settings)
{

    //settings = observer.update_settings(load_settings);
    for (auto& obj: objs)
        obj->settings_update(settings);

    // window.setFramerateLimit(settings.fps);

    // world = World{settings.world_map, '1' , 100};

    // if (pos != sf::Vector2f{settings.cmr.cmr_pos_x, settings.cmr.cmr_pos_y})
    // {
    //     cmr.set_position(settings.cmr.cmr_pos_x, settings.cmr.cmr_pos_y);
    //     pos = cmr.get_position();
    // }

    // cmr.set_speed(settings.cmr.speed);

    // cmr.set_n_rays(settings.cmr.n_rays);

    // cmr.set_visual_range(settings.cmr.vis_r);

    // cmr.set_rotation_speed(settings.cmr.rot_speed);

}
void Settings_Updater::add_updater(std::unique_ptr<ISettingsUpdater> obj)
{
    objs.push_back(std::move(obj));
}
