#include "delaunay.h"
#include "types.h"
#include <vector>
#include <cstdio>
#include <SFML/Graphics.hpp>

#define SCREENW 400
#define SCREENH 400
#define SCALE 50

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Triangles");
    std::vector<Vec2> cloud = {(Vec2){1, 1}, (Vec2){1, -1}, (Vec2){-1, 1}, (Vec2){-1, -1}};
    std::vector<Triangle2> triangulated = get_bowyer_watson(cloud);
    std::printf("%ld\n", triangulated.size());
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (Triangle2 &item : triangulated) {
            sf::ConvexShape shape(3);
            shape.setPoint(0, sf::Vector2f((item.m_p1.x * 10) + 200, (-(item.m_p1.y * 10) + 200)));
            shape.setPoint(1, sf::Vector2f((item.m_p2.x * 10) + 200, (-(item.m_p2.y * 10) + 200)));
            shape.setPoint(2, sf::Vector2f((item.m_p3.x * 10) + 200, (-(item.m_p3.y * 10) + 200)));
            shape.setFillColor(sf::Color::Black);
            shape.setOutlineThickness(1);
            shape.setOutlineColor(sf::Color::Yellow);
            window.draw(shape);
        }
        window.display();
    }
    return 0;
};
