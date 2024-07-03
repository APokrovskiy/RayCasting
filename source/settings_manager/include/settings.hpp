#pragma once
#include "World.hpp"
#include <nlohmann/json.hpp>

struct ray_casting_settings
{
    unsigned int fps_limit;     // Максимальный FPS

    World::World_String_Map string_map; // текстовая карта из строк

    struct camera
    {
        int cmr_pos_x;       // Координата x
        int cmr_pos_y;       // Координата y
        double speed;        // Скорость
        unsigned int n_rays; // Количество лучей
        unsigned int vis_r;  // Дальность видимости
    } cmr;
};

ray_casting_settings load_settings(const nlohmann::json &settings_json);
