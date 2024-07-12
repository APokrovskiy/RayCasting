#pragma once
#include "World.hpp"
#include "json.hpp"

struct ray_casting_settings
{
    unsigned int fps;     // Максимальный FPS

    World::World_String_Map world_map; // текстовая карта из строк

    struct vis_widgets
    {
        bool fps;
        bool minimap;
    } vis_widgets;

    struct camera
    {
        int cmr_pos_x;       // Координата x
        int cmr_pos_y;       // Координата y
        double speed;        // Скорость
        unsigned int n_rays; // Количество лучей
        unsigned int vis_r;  // Дальность видимости
        double rot_speed;    // Скорость поворота
    } cmr;
};

ray_casting_settings load_settings(const nlohmann::json &settings_json);
