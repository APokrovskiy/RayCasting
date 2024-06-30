#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <thread>  
#include <atomic>  
#include <fstream>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>


#include "World.hpp"


#include "Camera.hpp"
#include "Button.hpp"
#include "start_configurator.hpp"
#include "Settings_Updater.hpp"
#include "Background.hpp"

using json = nlohmann::json;







void upload_settings(const ray_casting_settings& settings, Camera& cmr)
{
    cmr.set_position(settings.cmr.cmr_pos_x, settings.cmr.cmr_pos_y);
    cmr.set_field_of_view(settings.cmr.fov);
    cmr.set_rotation(settings.cmr.rot_a);
    cmr.set_speed(settings.cmr.speed);
    cmr.set_n_rays(settings.cmr.n_rays);
    cmr.set_visual_range(settings.cmr.vis_r);
}


//TODO: Обновить список хедеров

// main.cpp
///////////////////////////////////////////////////////////////////////////////////////////////// 
int main()
{
    std::atomic_bool is_configurator_opened {false};

    
    std::string title = "Ray-Casting";
    std::string settings_file_path = "settings.json";

    // Создание файла, если его нет (CORRECT)
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::ifstream settings_file(settings_file_path);
    if (!settings_file)
    {
        start_configurator(is_configurator_opened);
        while (!settings_file)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            settings_file.clear();
            settings_file.open(settings_file_path);
        }
    }
    settings_file.close();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////


    Settings_Updater setts_updater{settings_file_path};

    ray_casting_settings settings = setts_updater.get_settings();
    // Обновление настроек
    





    // Инициализация объектов
    sf::RenderWindow window{{settings.win.screen_width, settings.win.screen_height}, title, sf::Style::Close | sf::Style::Titlebar};

    World world{settings.world.string_map,
            settings.world.wall_char,
            settings.world.tile_size};

    Camera cmr{world, 50};

    Background background{settings}; // TODO: Убрать зависимость от всей структуры настроек

    Button menu_button {"../Media/GUI/ButtonsIcons/MenuButton.png"}; 
    menu_button.set_scale({0.45,0.45});
    int menu_button_shift = 12; // Смещение кнопки от границ окон
    menu_button.set_position({settings.win.screen_width - menu_button.get_texture().getSize().x * menu_button.get_scale().x - menu_button_shift, menu_button_shift });


    // Загрузка настроек в камеру
    upload_settings(settings, cmr);
    


    // Главный цикл
    while (window.isOpen())
    {
        setts_updater.update(window, world, cmr, background, menu_button);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if(event.type == sf::Event::MouseButtonReleased && menu_button.isClicked(window,event.mouseButton))
                    // Создание потока с конфигуратором
                    start_configurator(is_configurator_opened);

        }

        if(window.hasFocus())
            cmr.move();

        window.clear();

        background.draw(window);

        cmr.draw(window, Camera::Rendering_Mode::M_3D);

        menu_button.draw(window);
        
        window.display();
    }
    
    return 0;
}
