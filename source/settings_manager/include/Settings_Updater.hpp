#pragma once

#include <string>

#include "Observer/JSON_File_Observer.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Button.hpp"
#include "Background.hpp"
#include "settings.hpp"




class Settings_Updater
{
public:
    Settings_Updater(const std::string& path_to_settings_file);
    void update(sf::RenderWindow& window, World& world, Camera& cmr, Background& background, Button& menu_button);
    bool is_file_changed();
    const ray_casting_settings& get_settings() const { return settings; }
private:
    JSON_File_Observer<ray_casting_settings> observer;

    ray_casting_settings settings;

    // Переменные состояния
    sf::VideoMode win_size{};
    sf::Vector2f pos{};
    double rot_a{};
    int menu_button_shift{15}; // Смещение кнопки от границ окон
};