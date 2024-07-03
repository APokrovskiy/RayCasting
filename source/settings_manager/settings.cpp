#include "settings.hpp"

ray_casting_settings load_settings(const nlohmann::json &settings_json)
{

    ray_casting_settings settings;

    settings.fps_limit = settings_json["fps_limit"];
    settings.string_map = settings_json["world_map"];
    settings.cmr.cmr_pos_x = settings_json["camera"]["position"][0];
    settings.cmr.cmr_pos_y = settings_json["camera"]["position"][1];
    settings.cmr.speed = settings_json["camera"]["speed"];
    settings.cmr.n_rays = settings_json["camera"]["n_rays"];
    settings.cmr.vis_r = settings_json["camera"]["visual_range"];

    return settings; // TODO: Реализовать семантику перемещения
}