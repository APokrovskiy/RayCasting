#pragma once
#include <SFML/Graphics.hpp>

class FPSLabel
{
public:

    FPSLabel(sf::RenderWindow *win);

    void update();
    void draw();
    void operator++(int);

private:
    int fps{};
    sf::RenderWindow *win;
    sf::Text fpslabel;
    sf::Font font;
    sf::Clock clock;
};