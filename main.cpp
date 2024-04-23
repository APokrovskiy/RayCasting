// Подключение библиотек
#include <set>
#define _USE_MATH_DEFINES
#include <math.h>
#include<SFML/Graphics.hpp>

// Карта мира (Можно изменять)
std::vector<std::string> text_map
{
    "1111111111",
    "1000110001",
    "1010001101",
    "1011100101",
    "1000001101",
    "1001001101",
    "1000001101",
    "1011000001",
    "1000001101",
    "1111111111"
};


const int FPS = 30; 
const int WIDTH = 1550, HEIGHT = 1440;
const int TILE = 100;
const int N_RAYS = 120;
const int VISIBILITY_RANGE = WIDTH;
const double FIELD_OF_VIEW = M_PI / 3;

std::set<std::pair<int, int>> init_world_map(std::vector<std::string> &text_map) {
    std::set<std::pair<int, int>> res;
    for (int y = 0; y < text_map.size(); y++)
        for (int x = 0; x < text_map[y].size(); x++)
            if (text_map[y][x] == '1')
                res.emplace(x, y);
    return res;
}

class Player {
    sf::Vector2f pos; 
    float speed; 
    float rot_angle{}; 
public:
    Player(float x, float y, float speed = 2) : pos(x, y), speed(speed) {}

    sf::Vector2f get_position() { return pos; }
    float get_rotation_angle() { return rot_angle; }

    void move() {
        double cos_a = cos(rot_angle),
               sin_a = sin(rot_angle);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            pos.x += speed * cos_a;
            pos.y += speed * sin_a;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            pos.x += speed * sin_a; 
            pos.y -= speed * cos_a;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pos.x -= speed * cos_a;
            pos.y -= speed * sin_a;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            pos.x -= speed * sin_a;
            pos.y += speed * cos_a;
        }  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            rot_angle -= 0.02; 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            rot_angle += 0.02; 
    }
};

sf::VertexArray create_line(const sf::Vector2f& start, const sf::Vector2f& end, sf::Color color = sf::Color::White) {
    sf::VertexArray line{ sf::Lines, 2 };
    line[0] = start;
    line[1] = end;
    line[0].color = color;
    line[1].color = color;
    return line;
}

class Ray_Caster {
    double field_of_view;
    int    num_rays;
    int    vis_range;

    double scale;
    double delta_angle;
    double dist_to_scrn;
    float  projection_coeff;
public:
    Ray_Caster(double fov, int n_rays, int vis_range)
            :field_of_view(fov), num_rays(n_rays), vis_range(vis_range){
        delta_angle = fov / num_rays;
        dist_to_scrn = num_rays / (2 * std::tan(fov / 2));
        projection_coeff = 5 * dist_to_scrn * TILE;
        scale = (double)WIDTH / n_rays;
    }

    void ray_casting(sf::RenderWindow& win, Player& pl, const std::set<std::pair<int, int>>& world_map) {
        double cur_angle = pl.get_rotation_angle() - field_of_view / 2;
        for (int i = 0; i < num_rays; i++) {
            double sin_a = sin(cur_angle),
                   cos_a = cos(cur_angle);
            for (int depth = 0; depth < vis_range; depth++) {
                double x = pl.get_position().x + depth * cos_a,
                       y = pl.get_position().y + depth * sin_a;
                
                if (std::find(world_map.begin(), world_map.end(), std::pair<int, int>{x / TILE, y / TILE}) != world_map.end()) {
                    depth *= cos(pl.get_rotation_angle() - cur_angle);
                    float projection_wall_height = projection_coeff / depth;
                    sf::Uint8 r_color = 255 / (1 + depth  * 0.004);
                    sf::RectangleShape r{ sf::Vector2f{(float)scale, projection_wall_height} };
                    r.setPosition(sf::Vector2f{  i * (float)scale,HEIGHT/2 - projection_wall_height / 2 });
                    r.setFillColor(sf::Color{ r_color, r_color, r_color });
                    win.draw(r);
                    break;
                }
            }
            cur_angle += delta_angle;
        }
        
    }
};

int main() {
    sf::RenderWindow window{ sf::VideoMode{WIDTH, HEIGHT}, "Ray-Casting" };
    window.setFramerateLimit(FPS);
     
    auto world_map = init_world_map(text_map);
    Player player{ WIDTH / 2,HEIGHT / 2}; 

    Ray_Caster ray_caster{
        FIELD_OF_VIEW,
        N_RAYS,
        VISIBILITY_RANGE
    };
    
    while (window.isOpen()){   
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();

        player.move();
        ray_caster.ray_casting(window, player, world_map);

        window.display();

    }
}
