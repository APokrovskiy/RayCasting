#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <thread>  // для использования std::thread
#include <atomic>  // для использования std::atomic
#include<fstream>

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>


#include "World.hpp"
#include "Camera.hpp"
#include "Button.cpp"
#include "system_without_console.hpp"

using json = nlohmann::json;



int main()
{
    //sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    //const unsigned SCRN_HEIGHT = desktop.height / 3 * 2;
    //const unsigned SCRN_WIDTH = desktop.width / 2;

    //импорт настроек json

    std::ifstream settings_file("./RayCastingConfigurator/settings.json");
    json settings_json = json::parse(settings_file);

    //задание констант

    const unsigned SCRN_WIDTH = settings_json["window"]["screen_size"][0];
    const unsigned SCRN_HEIGHT = settings_json["window"]["screen_size"][1];
    const std::string TITLE = settings_json["window"]["title"];

    //создание окна

    sf::RenderWindow window{{SCRN_WIDTH, SCRN_HEIGHT},TITLE, sf::Style::Close | sf::Style::Titlebar};
    window.setFramerateLimit(settings_json["window"]["fps_limit"]);

    //создание мира и камеры

    World wrld{settings_json["world"]["world_map"],
            settings_json["world"]["wall_char"].get<std::string>()[0],
            settings_json["world"]["tile_size"]};

    Camera cmr{wrld};

    //настройка камеры

    cmr.set_position(settings_json["camera"]["position"][0], settings_json["camera"]["position"][1]);
    cmr.set_field_of_view(settings_json["camera"]["field_of_view"]);
    cmr.set_rotation(settings_json["camera"]["rotation_angle"]);
    cmr.set_speed(settings_json["camera"]["speed"]);
    cmr.set_n_rays(settings_json["camera"]["n_rays"]);
    cmr.set_visual_range(settings_json["camera"]["visual_range"]);

    //настройка окруженя

    sf::RectangleShape clouds, floor;
    clouds.setFillColor(sf::Color{0,0,100});
    floor.setFillColor(sf::Color{0,100,0});
    clouds.setPosition({0,0});
    floor.setPosition({0, SCRN_HEIGHT / 2});
    clouds.setSize({SCRN_WIDTH, SCRN_HEIGHT / 2});
    floor.setSize({SCRN_WIDTH, SCRN_HEIGHT / 2});


    //главный цикл
    
    Button menu_button("../Media/GUI/ButtonsIcons/MenuButton.png",{SCRN_WIDTH-64,32});
    std::atomic_bool is_configurator_opened {false};

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::MouseButtonReleased )
            {
                if(menu_button.isClicked(window,event.mouseButton))
                {   
                    if (!is_configurator_opened.load()) // если поток с конфигуратором не создан => то создать
                    {
                        // Создание потока с конфигуратором
                        std::thread([&] {
                            is_configurator_opened.store(true);
                            system_without_console_output(L"python ./RayCastingConfigurator/Configurator.pyw");
                            is_configurator_opened.store(false);
                        }).detach();
                    }
                    else; // ничего ни делать
                }
            }
            
                
        }

        if(window.hasFocus())
            cmr.move();

        window.clear();

        window.draw(floor);
        window.draw(clouds);

        cmr.draw(window, Camera::Rendering_Mode::M_3D);

        menu_button.draw(window);
        
        window.display();
    }
    
    return 0;
}
