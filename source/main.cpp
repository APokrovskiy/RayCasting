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

#include "world_map/Map.hpp" // TODO: Добавить один хедер который добавляет эти две карты
#include "world_map/MiniMap.hpp"
#include "Button.hpp"
#include "start_configurator.hpp"
#include "Settings_Updater.hpp"
#include "Background.hpp"

using json = nlohmann::json;

// TODO: Обновить список хедеров

// main.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::atomic_bool is_configurator_opened{false};

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

    // Обновление настроек
    Settings_Updater setts_updater{settings_file_path};
    ray_casting_settings settings = setts_updater.get_settings();

    sf::VideoMode screen_res = sf::VideoMode::getDesktopMode();

    // Инициализация объектов
    sf::RenderWindow window{{screen_res.width / 2, screen_res.height / 3 * 2}, title};

    World world{settings.string_map, '1', 100};

    Camera cmr{world, 50};

    MiniMap mini_map{world, cmr, {0, 0}, {200, 200}, 0.1, {200, 200, 200}, {100, 100, 100}, {0, 0, 0}};
    Map map{world, cmr, {100, 100}, 0.5, {20, 20, 20}, {100, 100, 100}, 10};

    Background background{window.getSize().x, window.getSize().y}; // TODO: Убрать зависимость от всей структуры настроек
    int menu_button_shift{15};
    Button menu_button{"../Media/GUI/ButtonsIcons/MenuButton.png"};
    menu_button.set_scale({0.45, 0.45});

    setts_updater.update(window, world, cmr, background, menu_button);
    menu_button.set_position({window.getSize().x - menu_button.get_texture().getSize().x * menu_button.get_scale().x - menu_button_shift, menu_button_shift});

    // Главный цикл
    bool is_map_open = false;
    while (window.isOpen())
    {
        if (setts_updater.is_file_changed())
            setts_updater.update(window, world, cmr, background, menu_button);

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

        // движение камеры
        if (window.hasFocus() && !is_map_open)
            cmr.move();
        
        window.clear();

        // отрисовка заднего фона
        background.draw(window);
        // отрисовка вида камеры алгоритмом Ray Casting
        cmr.draw(window, Camera::Rendering_Mode::M_3D);
        // отрисовка мини карты
        mini_map.draw(window);

        // отрисовка кнопки меню настроек
        menu_button.draw(window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        {
            is_map_open = true;
            // отрисовка карты
            map.move();
            // движение карты
            map.draw(window);
        }
        else if (is_map_open)
        {
            map.set_position(cmr.get_position());
            is_map_open = false;
        }

        window.display();
    }

    return 0;
}
