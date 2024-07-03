#include "settings.hpp"

ray_casting_settings load_settings(const nlohmann::json &settings_json)
{

    ray_casting_settings settings;

    settings.win.screen_width = static_cast<unsigned int>(settings_json["window"]["screen_size"][0]);
    settings.win.screen_height = static_cast<unsigned int>(settings_json["window"]["screen_size"][1]);
    settings.win.fps_limit = settings_json["window"]["fps_limit"];
    settings.world.string_map = settings_json["world"]["world_map"];
    settings.world.wall_char = settings_json["world"]["wall_char"].get<std::string>()[0];
    settings.world.tile_size = settings_json["world"]["tile_size"];
    settings.cmr.cmr_pos_x = settings_json["camera"]["position"][0];
    settings.cmr.cmr_pos_y = settings_json["camera"]["position"][1];
    settings.cmr.fov = settings_json["camera"]["field_of_view"];
    settings.cmr.rot_a = settings_json["camera"]["rotation_angle"];
    settings.cmr.speed = settings_json["camera"]["speed"];
    settings.cmr.n_rays = settings_json["camera"]["n_rays"];
    settings.cmr.vis_r = settings_json["camera"]["visual_range"];

    return settings; // TODO: Реализовать семантику перемещения
}