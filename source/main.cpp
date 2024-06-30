#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>

#include "World.hpp"
#include "Camera.hpp"
#include "Map.hpp"
#include "MiniMap.hpp"


std::vector<std::string> text_map = 
{
    "1111111111111111111111",
    "1000000000000000000001",
    "1000001000000001000001",
    "1000000000000000000001",
    "1000000010000100000001",
    "1000000001111000000001",
    "1000000010000100000001",
    "1000000000000000000001",
    "1000001000000001000001",
    "1000010000000000100001",
    "1111111111111111111111"
};



int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned SCRN_HEIGHT = desktop.height / 3 * 2;
    const unsigned SCRN_WIDTH = desktop.width / 2;

    sf::RenderWindow window{{SCRN_WIDTH, SCRN_HEIGHT},"Ray-Casting", sf::Style::Close | sf::Style::Titlebar};
    window.setFramerateLimit(1000);

    World wrld{text_map,'1', /*TILE*/ 100};
    Camera cmr{wrld};
    MiniMap mini_map{wrld, cmr, {0,0}, {100,100}, 0.1, {200,200,200}, {100,100,100}, {0,0,0}};
    
    cmr.set_position(250,250);
    cmr.set_field_of_view(M_PI / 3);
    cmr.set_rotation(0);
    cmr.set_speed(3);
    cmr.set_n_rays(1000);
    cmr.set_visual_range(3000);
    
    sf::RectangleShape clouds, floor;
    clouds.setFillColor(sf::Color{0,0,100});
    floor.setFillColor(sf::Color{0,100,0});
    clouds.setPosition({0,0});
    floor.setPosition({0, SCRN_HEIGHT / 2});
    clouds.setSize({SCRN_WIDTH, SCRN_HEIGHT / 2});
    floor.setSize({SCRN_WIDTH, SCRN_HEIGHT / 2});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        
        cmr.move();

        window.clear();
        
        window.draw(floor);
        window.draw(clouds);

        cmr.draw(window, Camera::Rendering_Mode::M_3D);
        mini_map.draw(window);
        window.display();
    }
    
    return 0;
}
