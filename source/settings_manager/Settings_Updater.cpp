#include "Settings_Updater.hpp"

#include <string>
#include <iostream>
#include "Observer/JSON_File_Observer.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Background.hpp"
#include "Button.hpp"



Settings_Updater::Settings_Updater(const std::string& path_to_settings_file) : observer(path_to_settings_file)
{
    settings = observer.update_settings(load_settings);

}

bool Settings_Updater::is_file_changed()
{
    return observer.is_file_changed();
}

void Settings_Updater::update(sf::RenderWindow& window, World& world, Camera& cmr, Background& background, Button& menu_button)
{

        std::cout << "True\n";
        settings = observer.update_settings(load_settings);

        if (win_size != sf::VideoMode{settings.win.screen_width, settings.win.screen_height})
        {
            window.close(); // закрыть текущее окно

            win_size = {settings.win.screen_width, settings.win.screen_height};
            window.create(win_size, "Ray-Casting", sf::Style::Close | sf::Style::Titlebar); // TODO: Сделать что-то с TITLE

        } 

        window.setFramerateLimit(settings.win.fps_limit);

        world.set_tile(settings.world.tile_size);
        world.set_walls_coords(settings.world.string_map, settings.world.wall_char);

        if (pos != sf::Vector2f{settings.cmr.cmr_pos_x, settings.cmr.cmr_pos_y})
        {
            cmr.set_position(settings.cmr.cmr_pos_x, settings.cmr.cmr_pos_y);
            pos = cmr.get_position();
        }

        cmr.set_field_of_view(settings.cmr.fov);

        if (rot_a != settings.cmr.rot_a)
        {
            rot_a = settings.cmr.rot_a;
            cmr.set_rotation(rot_a);
        }

        cmr.set_speed(settings.cmr.speed);

        cmr.set_n_rays(settings.cmr.n_rays);

        cmr.set_visual_range(settings.cmr.vis_r);

        
        background.update();

        menu_button.set_position({settings.win.screen_width - menu_button.get_texture().getSize().x * menu_button.get_scale().x - menu_button_shift, menu_button_shift });
}

