#pragma once 
#include "World.hpp"
#include <nlohmann/json.hpp>

struct ray_casting_settings
{
    struct window
    {
        unsigned int            screen_width; // Ширина окна
        unsigned int            screen_height; // Высота окна
        unsigned int            fps_limit; // Максимальный FPS
    } win;

    struct world
    {
        World::World_String_Map string_map; // текстовая карта из строк
        char                    wall_char; // символ для стен на текстовой карте
        unsigned int            tile_size; // Размер плитки карты
    } world;

    struct camera
    {
        int                     cmr_pos_x; // Координата x 
        int                     cmr_pos_y; // Координата y 
        double                  fov; // Угол обзора
        double                  rot_a; // Угол поворота
        double                  speed; // Скорость
        unsigned int            n_rays; // Количество лучей
        unsigned int            vis_r; // Дальность видимости
    } cmr;
};

ray_casting_settings load_settings(const nlohmann::json& settings_json);
