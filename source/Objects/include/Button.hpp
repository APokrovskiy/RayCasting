#pragma once

#include <SFML/Graphics.hpp>

class Button 
{
public:
    Button(const std::string& file_path, sf::Vector2f pos={0,0},sf::Vector2f scale={1,1});

    Button(sf::Texture& texture, sf::Vector2f pos={0,0},sf::Vector2f scale={1,1});


    // Геттеры

    sf::Vector2f get_position() { return sprite.getPosition(); }
    sf::Vector2f get_scale() { return sprite.getScale(); }
    sf::Texture get_texture() { return *sprite.getTexture(); }


    // Сеттеры
    
    void set_position(sf::Vector2f pos);
    void set_scale(sf::Vector2f scale);
    void set_texture(sf::Texture texture);
    void set_texture(const std::string& file_path);
    

    // Функции-члены

    void draw(sf::RenderWindow& window);
    bool isMouseOver(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window,sf::Event::MouseButtonEvent event);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};