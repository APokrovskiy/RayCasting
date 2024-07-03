#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <exception>
#include <string>
using namespace std::string_literals;

Button::Button(const std::string &file_path, sf::Vector2f pos, sf::Vector2f scale)
{
    if (!texture.loadFromFile(file_path))
        std::runtime_error(("The button texture was not loaded along the path "s + file_path + '\n').c_str());

    sprite.setTexture(texture);
    sprite.setPosition(pos);
    sprite.setScale(scale);
}

Button::Button(sf::Texture &texture, sf::Vector2f pos, sf::Vector2f scale)
{
    sprite.setTexture(texture);
    sprite.setPosition(pos);
    sprite.setScale(scale);
}

// Сеттеры

void Button::set_position(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Button::set_scale(sf::Vector2f scale)
{
    sprite.setScale(scale);
}

void Button::set_texture(sf::Texture texture)
{
    sprite.setTexture(texture);
}

void Button::set_texture(const std::string &file_path)
{
    if (!texture.loadFromFile(file_path))
        std::runtime_error(("The button texture was not loaded along the path "s + file_path + '\n').c_str());

    sprite.setTexture(texture);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

// Функции-члены

bool Button::isMouseOver(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f buttonPos = sprite.getPosition();
    sf::Vector2f buttonSize = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

    return mousePos.x > buttonPos.x && mousePos.x < buttonPos.x + buttonSize.x &&
           mousePos.y > buttonPos.y && mousePos.y < buttonPos.y + buttonSize.y;
}

bool Button::isClicked(sf::RenderWindow &window, sf::Event::MouseButtonEvent event)
{
    if (event.button == sf::Mouse::Left && isMouseOver(window))
        return true;

    return false;
}
