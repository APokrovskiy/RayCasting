#define _USE_MATH_DEFINES
#include "./ray-cast.hpp"

#include <cmath>
#include <iostream>

bool rc::Coords::operator==(rc::Coords other)
{
    return (this->x == other.x) && (this->y == other.y);
}

bool rc::Coords::operator!=(rc::Coords other)
{
    return !(*this == other);
}

bool rc::Coords::operator<(const Coords &other) const
{
    if (this->x < other.x)
    {
        return true;
    }
    if (other.x < this->x)
    {
        return false;
    }

    return this->y < other.y;
}

std::set<rc::Coords> rc::init_world_map(std::vector<std::string> &text_map, char wall)
{
    std::set<rc::Coords> res;
    for (int y = 0; y < text_map.size(); y++)
        for (int x = 0; x < text_map[y].size(); x++)
        {
            if (text_map[y][x] == wall)
            {
                res.emplace(x, y);
            }
        }

    return res;
}

double rc::radians_normalise(double angle_in_radians)
{
    while (angle_in_radians >= 2 * M_PI)
    {
        angle_in_radians -= 2 * M_PI;
    }
    while (angle_in_radians < 0)
    {
        angle_in_radians += 2 * M_PI;
    }

    return angle_in_radians;
}

unsigned int rc::ray_cast(const std::set<rc::Coords> &wm, int cell_sz, rc::Coords cmr, double rot_a, unsigned int vis_r)
{
    // 0 <= rot_angle <= 2 * M_PI
    rot_a = radians_normalise(rot_a);

    // Использованные переменные
    //////////////////////////////////////////////////////////////
    int va, vb, ha, hb;                                        // Катеты треугольников
    double BAC, EAD;                                           // Углы треугольников
    Coords dcell, vintersection, hintersection, vcell, hcell;  // Координаты пересечения и ячейки, с которыми лучи пересекаются
    bool vray_is_completed = false, hray_is_completed = false; // Луч перестал искать пересечения по вертикальным/горизонтальным линиям?
    //////////////////////////////////////////////////////////////

    // Определение углов треугольников
    ///////////////////////////////////////////////////////////
    if (rot_a >= 0 && rot_a <= M_PI_2)
    {
        BAC = rot_a;
        EAD = M_PI_2 - rot_a;
    }
    else if (rot_a >= M_PI_2 && rot_a <= M_PI)
    {
        BAC = M_PI - rot_a;
        EAD = M_PI_2 - BAC;
    }
    else if (rot_a >= M_PI && rot_a <= 3 * M_PI / 2)
    {
        BAC = rot_a - M_PI;
        EAD = 3 * M_PI / 2 - rot_a;
    }
    else if (rot_a >= 3 * M_PI_2)
    {
        BAC = 2 * M_PI - rot_a;
        EAD = M_PI_2 - (2 * M_PI - rot_a);
    }
    ///////////////////////////////////////////////////////////

    // Определение катетов треугольников
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    va = (cmr.x / cell_sz + 1) * cell_sz - cmr.x; // Если (x > 0) на тригонометрической окружности
    if (rot_a >= M_PI_2 && rot_a <= 3 * M_PI_2)   // Если (x < 0) на тригонометрической окружности
        va = cell_sz - va;

    ha = (cmr.y / cell_sz + 1) * cell_sz - cmr.y; // Если (y < 0) на тригонометрической окружности
    if (rot_a >= 0 && rot_a <= M_PI)              // Если (y > 0) на тригонометрической окружности
        ha = cell_sz - ha;

    vb = va * tan(BAC);
    hb = ha * tan(EAD);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (true)
    {
        // Если происходит переполнение, при расчете расстояния
        ////////////////////////////////////////////////////
        if (std::isnan(sqrt(va * va + vb * vb)))
            vray_is_completed = true;
        if (std::isnan(sqrt(ha * ha + hb * hb)))
            hray_is_completed = true;
        ////////////////////////////////////////////////////

        // Определение потенциальных координат пересечения
        ////////////////////////////////////////////////////////////////
        if (rot_a >= 0 && rot_a <= M_PI_2)
        {
            vintersection = {(cmr.x + va), (cmr.y - vb)};
            hintersection = {(cmr.x + hb), (cmr.y - ha) - cell_sz};
        }
        else if (rot_a >= M_PI_2 && rot_a <= M_PI)
        {
            vintersection = {(cmr.x - va) - cell_sz, (cmr.y - vb)};
            hintersection = {(cmr.x - hb), (cmr.y - ha) - cell_sz};
        }
        else if (rot_a >= M_PI && rot_a <= 3 * M_PI / 2)
        {
            vintersection = {(cmr.x - va) - cell_sz, (cmr.y + vb)};
            hintersection = {(cmr.x - hb), (cmr.y + ha)};
        }
        else if (rot_a >= 3 * M_PI_2)
        {
            vintersection = {(cmr.x + va), (cmr.y + vb)};
            hintersection = {(cmr.x + hb), (cmr.y + ha)};
        }
        ////////////////////////////////////////////////////////////////

        // Определение ячеек, с которыми пересекаются лучи
        //////////////////////////////////////////////////////////////////
        vcell = {vintersection.x / cell_sz, vintersection.y / cell_sz};
        hcell = {hintersection.x / cell_sz, hintersection.y / cell_sz};
        //////////////////////////////////////////////////////////////////

        // Поиск пересечения по вертикальным линиям
        if ((hb >= va || ha >= vb) || hray_is_completed)
        {
            if ((vintersection.x % cell_sz == 0) && (vintersection.y % cell_sz == 0)) // Если луч находится в точке пересечения 4 ячеек карты
            {
                dcell = {vcell.x, vcell.y};
                if (rot_a >= 0 && rot_a <= M_PI_2)
                    dcell.y--;
                else if (rot_a >= M_PI_2 && rot_a <= M_PI)
                    dcell.y--;

                if (wm.find(dcell) != wm.end())
                    return sqrt(va * va + vb * vb);
            }

            if (!vray_is_completed && (sqrt(va * va + vb * vb) < vis_r) && !(wm.find(vcell) != wm.end())) // Если стены нет
            {
                va += cell_sz;
                vb = va * tan(BAC);
            }
            else if (sqrt(va * va + vb * vb) >= vis_r) // Длина луча >= Дальности видимости
                vray_is_completed = true;
            else if (wm.find(vcell) != wm.end()) // Если стена есть
                return sqrt(va * va + vb * vb);
        }

        // Поиск пересечения по горизонтальным линиям
        if ((!(hb >= va || ha >= vb)) || vray_is_completed)
        {
            if ((hintersection.x % cell_sz == 0) && (hintersection.y % cell_sz == 0)) // Если луч находится в точке пересечения 4 ячеек карты
            {
                dcell = {hcell.x, hcell.y};
                if (rot_a >= M_PI_2 && rot_a <= M_PI)
                    dcell.x--;
                else if (rot_a >= M_PI && rot_a <= 3 * M_PI / 2)
                    dcell.x--;

                if (wm.find(dcell) != wm.end())
                    return sqrt(ha * ha + hb * hb);
            }

            if (!hray_is_completed && (sqrt(ha * ha + hb * hb) < vis_r) && !(wm.find(hcell) != wm.end())) // Если стены нет
            {
                ha += cell_sz;
                hb = ha * tan(EAD);
            }
            else if (sqrt(ha * ha + hb * hb) >= vis_r) // Длина луча >= Дальности видимости
                hray_is_completed = true;
            else if (wm.find(hcell) != wm.end()) // Если стена есть
                return sqrt(ha * ha + hb * hb);
        }

        if (vray_is_completed && hray_is_completed)
            return vis_r;
    }
}

std::vector<std::pair<unsigned int, double>> rc::ray_casting(const std::set<rc::Coords> &world_map, int cell_size, rc::Coords camera, double rotation_angle, unsigned int visual_range, double fov, int n_rays)
{
    std::vector<std::pair<unsigned int, double>> rays(n_rays);

    int i = 0;
    for (double cur_angle = rotation_angle - (fov / 2); i < n_rays; cur_angle += (fov / n_rays))
        rays[i++] = {rc::ray_cast(world_map, cell_size, camera, cur_angle, visual_range), cur_angle};
    return rays;
}