#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>

#include "World.hpp"
#include "Camera.hpp"

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
    sf::RenderWindow window{sf::VideoMode{1920, 1080},"Ray"};
    window.setFramerateLimit(144);

    World wrld{text_map,'1', /*TILE*/ 100};
    Camera cmr{wrld};
    
    cmr.set_position(50,50);
    cmr.set_field_of_view(M_PI / 3);
    cmr.set_rotation(0);
    cmr.set_speed(2);
    cmr.set_n_rays(1000);
    cmr.set_visual_range(5000);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        
        cmr.move();

        window.clear();

        cmr.draw(window, Camera::Rendering_Mode::M_3D);
        
        window.display();
    }

    std::cin.get();
    return 0;
}
