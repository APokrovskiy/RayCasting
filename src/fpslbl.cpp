#include "fpslbl.hpp"

FPSLabel::FPSLabel(sf::RenderWindow *win)
{
    if (win) this->win = win;
    else throw std::runtime_error("win ptr has null");

    clock.restart();
    font.loadFromFile("fonts/Ebbe.ttf");
    fpslabel.setFont(font);
    fpslabel.setFillColor(sf::Color::Red);
}

void FPSLabel::update()
{
    if (clock.getElapsedTime().asSeconds() >= 1) // TODO: Вынести это добро в класс
    {
        clock.restart();
        fpslabel.setString("fps: " + std::to_string(fps));
        fpslabel.setPosition(win->getSize().x / 2, 10); 
        fps = 0;
    }
}

void FPSLabel::draw()
{
    win->draw(fpslabel);
}

void FPSLabel::operator++(int)
{
    fps++;
}