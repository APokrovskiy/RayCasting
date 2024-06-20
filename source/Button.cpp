#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>


class Button {
public:

    Button(const std::string& filePath, sf::Vector2f pos={0,0},sf::Vector2f scale={1,1}) {
        if (!texture.loadFromFile(filePath)) {
            // Обработка ошибки загрузки текстуры
        }
        sprite.setTexture(texture);
        sprite.setPosition(pos);
        sprite.setScale(scale);
    }
    Button(sf::Texture& texture, sf::Vector2f pos={0,0},sf::Vector2f scale={1,1}) 
    {
        sprite.setTexture(texture);
        sprite.setPosition(pos);
        sprite.setScale(scale);
    }
    // Геттеры
    sf::Vector2f get_position()
    {
        return sprite.getPosition();
    }

    sf::Vector2f get_scale()
    {
        return sprite.getScale();
    }

    sf::Texture get_texture()
    {
        return *sprite.getTexture();
    }

    //Сеттеры
    

    void set_position(sf::Vector2f pos) {
        sprite.setPosition(pos);
        
    }
    void set_scale(sf::Vector2f scale) {
        sprite.setPosition(scale);
        
    }

    void set_texture(sf::Texture texture)
    {
            sprite.setTexture(texture);
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    bool isMouseOver(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f buttonPos = sprite.getPosition();
        sf::Vector2f buttonSize = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

        return mousePos.x > buttonPos.x && mousePos.x < buttonPos.x + buttonSize.x &&
               mousePos.y > buttonPos.y && mousePos.y < buttonPos.y + buttonSize.y;
    }
    bool isClicked(sf::RenderWindow& window,sf::Event::MouseButtonEvent event)
    {
        if(event.button == sf::Mouse::Left)
        {
            if(isMouseOver(window))
            {
                return true;
            }
        }
        return false;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};