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

#include "World.hpp"

#include "Camera.hpp"

#include "FPSLabel.hpp"
#include "world_map/Map.hpp" // TODO: Добавить один хедер который добавляет эти две карты
#include "world_map/MiniMap.hpp"
#include "Button.hpp"
#include "start_configurator.hpp"
#include "settings_manager/Settings_Updater.hpp"
#include "settings_manager/Settings_Observer.hpp"
#include "settings.hpp"
#include "Background.hpp"

// TODO: Обновить список хедеров
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

// main.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::atomic_bool is_configurator_opened{false};

    std::string title = "Ray-Casting";
    std::string settings_file_path = "settings.json";

    // Создание файла, если его нет
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

    

    Settings_Observer<ray_casting_settings> file_observer{settings_file_path};
    ray_casting_settings settings = file_observer.update_settings(load_settings);

    
    

    sf::VideoMode screen_res = sf::VideoMode::getDesktopMode();


    sf::RenderWindow window{{screen_res.width / 2, screen_res.height / 3 * 2}, title};
    World world{settings.world_map, '1', 100};
    Camera cmr{world, 50};

    MiniMap mini_map{&world, &cmr};
    Map map{&world, &cmr};
    map.set_multiply(0.5);

    Background background{window.getSize().x, window.getSize().y}; 
    Button menu_button{"./gui/ButtonsIcons/MenuButton.png"};
    int menu_button_shift{15};
    menu_button.set_scale({0.45, 0.45});

    Settings_Updater settings_updater;
    settings_updater.add_updater(std::unique_ptr<CameraSettingsUpdater>{new CameraSettingsUpdater{cmr}});
    settings_updater.add_updater(std::unique_ptr<WorldSettingsUpdater>{new WorldSettingsUpdater{world}});
    settings_updater.add_updater(std::unique_ptr<WindowSettingsUpdater>{new WindowSettingsUpdater{window}});

    settings_updater.update(settings);
    menu_button.set_position({window.getSize().x - menu_button.get_texture().getSize().x * menu_button.get_scale().x - menu_button_shift, menu_button_shift});

    FPSLabel fps{&window};

    // Главный цикл
    bool is_map_open = false;
    while (window.isOpen())
    {
        if (file_observer.is_file_changed())
        {
            settings = file_observer.update_settings(load_settings);
            settings_updater.update(settings);
        }

        

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonReleased && menu_button.isClicked(window, event.mouseButton))
                // Создание потока с конфигуратором
                start_configurator(is_configurator_opened);

                
            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                background.update(window.getSize().x, window.getSize().y);
                menu_button.set_position({window.getSize().x - menu_button.get_texture().getSize().x * menu_button.get_scale().x - menu_button_shift, menu_button_shift});
            }
        }

        //расчет фпс
        if (settings.vis_widgets.fps)
            fps.update();

        if (window.hasFocus() && !is_map_open)
            cmr.move();
        
        window.clear();

        // отрисовка заднего фона
        background.draw(window);
        // отрисовка вида камеры алгоритмом Ray Casting
        cmr.draw(window, Camera::Rendering_Mode::M_3D);
        if (settings.vis_widgets.minimap)
            // отрисовка мини карты
            mini_map.draw(window);

        // отрисовка кнопки меню настроек
        menu_button.draw(window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) 
        {
            if(!is_map_open)
            {
                map.go_to_position(window, cmr.get_position());
            }
            is_map_open = true; 
            map.move();
            map.draw(window);
        }
        else if (is_map_open)
            is_map_open = false;


        if (settings.vis_widgets.fps)
            fps.draw();

        window.display();

        if (settings.vis_widgets.fps)
            fps++;
    }

    return 0;
}
