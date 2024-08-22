#include <atomic>

#include "setts/manager/observer.hpp"
#include "setts/manager/updater.hpp"
#include "background.hpp"
#include "minimap.hpp"
#include "fpslbl.hpp"
#include "map.hpp"


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

// Временное решение
void create_settings_file()
{
    std::ofstream file{"settings.json"};
    std::string data{
    R"({                      
        "camera": {         
            "position": [   
                250,        
                250         
            ],              
            "speed": 3,         
            "n_rays": 100,          
            "rot_speed": 0.01,      
            "visual_range": 3000    
        },                          
        "vis_widgets": {            
            "fps": false,           
            "minimap": true         
        },                          
        "fps": 60,                  
        "world_map": [              
            "1111111111111111111111",   
            "1000000000000000000001",   
            "1000000000000000000001",   
            "1000000000000000000001",   
            "1000000000000000000001",   
            "1000000000000000000001",   
            "1000000000000000000001",   
            "1000000000000000000001",   
            "1000000000000000000001",   
            "1000000000000000000001",   
            "1111111111111111111111"    
        ]                               
    })"};
    file << data;
}

// main.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::atomic_bool is_configurator_opened{false};

    std::string title = "Ray-Casting";
    std::string settings_file_path = "settings.json";

    if (!std::filesystem::exists(settings_file_path))
    {
        create_settings_file();
    }
    
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

    Settings_Updater settings_updater;
    settings_updater.add_updater(std::unique_ptr<CameraSettingsUpdater>{new CameraSettingsUpdater{cmr}});
    settings_updater.add_updater(std::unique_ptr<WorldSettingsUpdater>{new WorldSettingsUpdater{world}});
    settings_updater.add_updater(std::unique_ptr<WindowSettingsUpdater>{new WindowSettingsUpdater{window}});

    settings_updater.update(settings);

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
            
            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                background.update(window.getSize().x, window.getSize().y);
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
